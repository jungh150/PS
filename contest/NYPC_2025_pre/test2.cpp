// 제출번호 81602: 4승 6패
// Yacht Auction AI (C++20, revised)
// - I/O protocol identical to sample-code.cpp
// - Strategic changes based on the postmortem:
//   1) If we predict NON-CONTESTED (상대가 다른 묶음 선호) → 입찰 0
//   2) CONTESTED일 때도 입찰 상한 = floor(0.5 * Δ가치)
//      - 상대가 "0원 성향"이면 동률 브레이크용 초소액만(ε) 사용 (단, ε ≤ 0.5Δ일 때만)
//      - 일반 상황은 부분 비례(진행도/점수차 반영) but 절대 0.5Δ 초과 금지
//   3) 점수 계산은 매 SCORE에서 남은 모든 규칙 × 10개 중 5개 조합 완전탐색
//   4) 상단 보너스(63,000→+35,000)를 즉시 가치에 반영
//

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ===== Rules =====
enum DiceRule {
    ONE, TWO, THREE, FOUR, FIVE, SIX,               // 0..5 (upper)
    CHOICE, FOUR_OF_A_KIND, FULL_HOUSE,             // 6..8
    SMALL_STRAIGHT, LARGE_STRAIGHT, YACHT           // 9..11
};

struct Bid { char group; int amount; };
struct DicePut { DiceRule rule; vector<int> dice; };

// ===== Enum-string =====
string toString(DiceRule rule) {
    switch (rule) {
        case ONE: return "ONE"; case TWO: return "TWO"; case THREE: return "THREE";
        case FOUR: return "FOUR"; case FIVE: return "FIVE"; case SIX: return "SIX";
        case CHOICE: return "CHOICE"; case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
        case FULL_HOUSE: return "FULL_HOUSE"; case SMALL_STRAIGHT: return "SMALL_STRAIGHT";
        case LARGE_STRAIGHT: return "LARGE_STRAIGHT"; case YACHT: return "YACHT";
    }
    assert(false); return "";
}
DiceRule fromString(const string& s) {
    if (s == "ONE") return ONE; if (s == "TWO") return TWO; if (s == "THREE") return THREE;
    if (s == "FOUR") return FOUR; if (s == "FIVE") return FIVE; if (s == "SIX") return SIX;
    if (s == "CHOICE") return CHOICE; if (s == "FOUR_OF_A_KIND") return FOUR_OF_A_KIND;
    if (s == "FULL_HOUSE") return FULL_HOUSE; if (s == "SMALL_STRAIGHT") return SMALL_STRAIGHT;
    if (s == "LARGE_STRAIGHT") return LARGE_STRAIGHT; if (s == "YACHT") return YACHT;
    assert(false); return ONE;
}

// ===== GameState & Scoring =====
struct GameState {
    vector<int> dice;          // 보유 주사위(값 1..6)
    vector<int> ruleScore;     // 각 규칙 점수(미사용 -1)
    int bidScore;              // 입찰 누계(성공: -, 실패: +)

    GameState() : ruleScore(12, -1), bidScore(0) {}

    int getTotalScore() const {
        int up = 0, low = 0, bonus = 0;
        for (int r = ONE; r <= SIX; ++r) if (ruleScore[r] != -1) up += ruleScore[r];
        if (up >= 63000) bonus = 35000;
        for (int r = CHOICE; r <= YACHT; ++r) if (ruleScore[r] != -1) low += ruleScore[r];
        return up + bonus + low + bidScore;
    }
    void bid(bool won, int amount) { bidScore += (won ? -amount : amount); }
    void addDice(const vector<int>& nd) { dice.insert(dice.end(), nd.begin(), nd.end()); }

    void useDice(const DicePut& put) {
        assert(ruleScore[put.rule] == -1 && "Rule already used");
        vector<int> pool = dice;
        for (int v : put.dice) {
            auto it = find(pool.begin(), pool.end(), v);
            assert(it != pool.end() && "Invalid dice");
            pool.erase(it);
        }
        dice.swap(pool);
        ruleScore[put.rule] = calculateScoreStatic(put.rule, put.dice);
    }

    static int calculateScoreStatic(DiceRule rule, const vector<int>& d) {
        array<int,7> cnt{}; for (int v : d) cnt[v]++;
        int sumAll = accumulate(d.begin(), d.end(), 0) * 1000;

        switch (rule) {
            case ONE:   return cnt[1]*1000;
            case TWO:   return cnt[2]*2000;
            case THREE: return cnt[3]*3000;
            case FOUR:  return cnt[4]*4000;
            case FIVE:  return cnt[5]*5000;
            case SIX:   return cnt[6]*6000;
            case CHOICE: return sumAll;
            case FOUR_OF_A_KIND: {
                for (int v=1; v<=6; ++v) if (cnt[v] >= 4) return sumAll;
                return 0;
            }
            case FULL_HOUSE: {
                bool has3=false, has2=false, has5=false;
                for (int v=1; v<=6; ++v) {
                    if (cnt[v]==3) has3 = true;
                    if (cnt[v]==2) has2 = true;
                    if (cnt[v]==5) has5 = true;
                }
                return (has5 || (has3 && has2)) ? sumAll : 0;
            }
            case SMALL_STRAIGHT: {
                auto has=[&](int v){return cnt[v]>0;};
                bool ok = (has(1)&&has(2)&&has(3)&&has(4)) ||
                          (has(2)&&has(3)&&has(4)&&has(5)) ||
                          (has(3)&&has(4)&&has(5)&&has(6));
                return ok ? 15000 : 0;
            }
            case LARGE_STRAIGHT: {
                auto has=[&](int v){return cnt[v]>0;};
                bool ok = (has(1)&&has(2)&&has(3)&&has(4)&&has(5)) ||
                          (has(2)&&has(3)&&has(4)&&has(5)&&has(6));
                return ok ? 30000 : 0;
            }
            case YACHT: {
                for (int v=1; v<=6; ++v) if (cnt[v]==5) return 50000;
                return 0;
            }
        }
        assert(false); return 0;
    }
};

// ===== Combinations: all 5-combos of indices [0..n) =====
static void choose5Indices(int n, vector<array<int,5>>& out) {
    array<int,5> idx{};
    auto dfs = [&](auto&& self, int i, int start) -> void {
        if (i == 5) { out.push_back(idx); return; }
        for (int s = start; s <= n - (5 - i); ++s) {
            idx[i] = s;
            self(self, i+1, s+1);
        }
    };
    dfs(dfs, 0, 0);
}

struct EvalResult {
    DiceRule rule{};
    vector<int> dice;
    int score{0};
    int extraBonus{0}; // +35,000 if this play crosses 63k upper threshold
    int effective() const { return score + extraBonus; }
};

static int currentUpperSum(const GameState& st) {
    int s=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]!=-1) s+=st.ruleScore[r]; return s;
}

static EvalResult evaluateBestPlay(const GameState& st, const vector<int>& inventory) {
    EvalResult best; bool hasAny=false;
    int n = (int)inventory.size();
    if (n < 5) return best;

    vector<array<int,5>> combs;
    if (n == 5) combs.push_back({0,1,2,3,4});
    else choose5Indices(n, combs);

    const int preUpper = currentUpperSum(st);

    for (int r=0; r<12; ++r) {
        if (st.ruleScore[r] != -1) continue;
        for (auto id : combs) {
            vector<int> hand = { inventory[id[0]],inventory[id[1]],inventory[id[2]],inventory[id[3]],inventory[id[4]] };
            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0;
            if (r>=ONE && r<=SIX) {
                int post = preUpper + sc;
                if (preUpper < 63000 && post >= 63000) extra = 35000;
            }
            if (!hasAny || sc+extra > best.score+best.extraBonus) {
                best.rule = (DiceRule)r; best.dice = hand; best.score = sc; best.extraBonus = extra; hasAny = true;
            }
        }
    }
    return best;
}

// 번들 가치(현재 보유 5개 + 후보 5개 → 이번 라운드 최대 유효득점)
static int evaluateBundleValue(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    return evaluateBestPlay(st, merged).effective();
}

// ===== Game with revised bidding =====
class Game {
public:
    GameState myState, oppState;

    int rollCount = 0;         // 1..12 (13라운드는 ROLL 없음)
    int seenOppBids = 0;       // 관측된 상대 입찰 횟수
    int oppNonZeroBids = 0;    // 그 중 0이 아닌 입찰 횟수
    Bid lastMyBid{'A', 0};

    // --- Bidding with non-contested detection & 0.5Δ cap ---
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // 내 "씨앗" 5개(보통 직전 라운드 잔여)
        vector<int> mySeed = myState.dice;
        if ((int)mySeed.size() > 5) {
            // 방어적 처리: 앞에서 5개만 사용(실전 플로우에서는 보통 정확히 5)
            mySeed.resize(5);
        }

        // 가치 평가
        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);
        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // 우리가 A/B 중 더 좋은 쪽과 나머지의 가치 차

        // 상대 선호 예측
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        int oValA = evaluateBundleValue(oppState, oppSeed, diceA);
        int oValB = evaluateBundleValue(oppState, oppSeed, diceB);
        char oppPref = (oValA > oValB) ? 'A' : 'B';

        // "논컨테스트" 판단: 상대 선호가 다르면 거의 확실히 비경쟁
        bool contested = (oppPref == myPref);

        // 상대의 0원 성향 추정(최근 로그 기반)
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80); // 80% 이상 0원

        // 진행도/점수차(일반 케이스에서만 사용)
        int myTotal = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // 내가 뒤지면 +
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // 입찰 상한: floor(0.5 * Δ)
        int cap = max(0, delta / 2);
        int amount = 0;

        if (!contested) {
            // 비경쟁이면 0이 최적
            amount = 0;
        } else if (cap <= 0) {
            amount = 0;
        } else {
            // 컨테스트 + 가치 있음
            if (oppLikelyZero) {
                // 상대가 0원 성향이면 동률 브레이크용 초소액만 사용(단, 0.5Δ 이내일 때만)
                int eps = 7 + (rollCount * 13) % 23;    // 작은 양의 수(가변)
                amount = (eps <= cap) ? eps : 0;
            } else {
                // 일반 케이스: 부분 비례 + 상한 적용
                // f ∈ [0.20 .. 0.60] 대략: 진행도/점수차에 따라 가중
                double f = 0.20 + 0.25 * progress + min(0.15, max(0.0, scoreDiff / 100000.0));
                int base = (int)llround(delta * f);
                amount = min(cap, max(0, base));

                // 그래도 0이면 동률 브레이크 소액(가능한 경우에만)
                if (amount == 0) {
                    int eps = 11; // 아주 작은 수
                    if (eps <= cap) amount = eps;
                }
            }
        }

        // 최소/최대 클램프
        amount = max(0, min(100000, amount));
        lastMyBid = Bid{ myPref, amount };
        return lastMyBid;
    }

    // --- Scoring (unchanged: 완전탐색 + 보너스 가치 반영) ---
    DicePut calculatePut() {
        EvalResult er = evaluateBestPlay(myState, myState.dice);
        if (er.dice.empty()) {
            int rule=-1; for (int i=0;i<12;++i) if (myState.ruleScore[i]==-1){rule=i;break;}
            vector<int> hand;
            for (int i=0;i<5 && i<(int)myState.dice.size(); ++i) hand.push_back(myState.dice[i]);
            while ((int)hand.size()<5 && !myState.dice.empty()) hand.push_back(myState.dice.back());
            return DicePut{ (DiceRule)rule, hand };
        }
        return DicePut{ er.rule, er.dice };
    }

    // --- State updates (same protocol as sample) ---
    void updateGet(const vector<int>& diceA, const vector<int>& diceB,
                   const Bid& myBid, const Bid& oppBid, char myGroup) {
        if (myGroup == 'A') { myState.addDice(diceA); oppState.addDice(diceB); }
        else                { myState.addDice(diceB); oppState.addDice(diceA); }

        bool myWon  = (myBid.group  == myGroup);
        bool oppWon = (oppBid.group == (myGroup=='A' ? 'B' : 'A'));
        myState.bid(myWon, myBid.amount);
        oppState.bid(oppWon, oppBid.amount);

        // 상대 입찰 관측 업데이트
        seenOppBids++;
        if (oppBid.amount > 0) oppNonZeroBids++;
    }

    void updatePut(const DicePut& put) { myState.useDice(put); }
    void updateSet(const DicePut& put) { oppState.useDice(put); }
};

// ===== Main (sample I/O compatible) =====
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Game game;
    vector<int> diceA, diceB;
    Bid myBid{'A', 0};

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string command; iss >> command;

        if (command == "READY") {
            cout << "OK\n" << flush;
        } else if (command == "ROLL") {
            string strA, strB; iss >> strA >> strB;
            diceA.clear(); diceB.clear();
            for (char c: strA) diceA.push_back(c - '0');
            for (char c: strB) diceB.push_back(c - '0');

            myBid = game.calculateBid(diceA, diceB);
            cout << "BID " << myBid.group << " " << myBid.amount << "\n" << flush;
        } else if (command == "GET") {
            char myGroup, oppGroup; int oppScore;
            iss >> myGroup >> oppGroup >> oppScore;
            game.updateGet(diceA, diceB, myBid, Bid{oppGroup, oppScore}, myGroup);
        } else if (command == "SCORE") {
            DicePut put = game.calculatePut();
            game.updatePut(put);
            cout << "PUT " << toString(put.rule) << " ";
            for (int v: put.dice) cout << v;
            cout << "\n" << flush;
        } else if (command == "SET") {
            string ruleStr, str; iss >> ruleStr >> str;
            vector<int> d; for (char c: str) d.push_back(c - '0');
            game.updateSet(DicePut{ fromString(ruleStr), d });
        } else if (command == "FINISH") {
            break;
        }
    }
    return 0;
}
