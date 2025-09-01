// 제출번호 83099: 4승 6패
// test3.cpp에서 평가 로직만 수정한 버전
// - I/O 프로토콜: sample-code.cpp와 동일
// - 반영 사항(요약):
//   1) OppEval 분리: 상대는 비상단 페널티 제거, 상단 경로 보정 약화, 즉시 하단(SS/LS/YACHT) 가중
//   2) 즉시 하단 하드-디나이(Hard-deny): 상대가 이번 턴에 SS/LS/YACHT 성립 가능 → 무조건 경합 전환 + 최소입찰 하한
//   3) 비경합/경합 바닥세: 비경합 tax 바닥(>=300), 경합 바닥(>=180)
//   4) 상단 보너스 인지형 스코어러(기존 test3의 bonus-aware v2 유지)
//
//  — 규칙 점수:
//    * ONE..SIX: 개수 * 눈 * 1000
//    * CHOICE: 합 * 1000
//    * 4-kind: ≥4개면 합 * 1000
//    * FULL_HOUSE: 3+2 또는 5-kind(YACHT) 허용 → 합 * 1000
//    * SS: 4연속(1234/2345/3456) 15000
//    * LS: 5연속(12345/23456) 30000
//    * YACHT: 5-kind 50000
//
//  — 빌드: C++20

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
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

// ===== Enum <-> String =====
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
    vector<int> dice;          // inventory (values 1..6)
    vector<int> ruleScore;     // per rule: -1 if unused
    int bidScore;              // win bid → minus, lose bid → plus

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
            assert(it != pool.end() && "Invalid dice selection");
            pool.erase(it);
        }
        dice.swap(pool);
        ruleScore[put.rule] = calculateScoreStatic(put.rule, put.dice);
    }

    // Single-hand scoring for 5 dice
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
                // Accepts 3+2 OR 5-kind(=YACHT)
                bool has3=false, has2=false, has5=false;
                for (int v=1; v<=6; ++v) {
                    has3 |= (cnt[v]==3);
                    has2 |= (cnt[v]==2);
                    has5 |= (cnt[v]==5);
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
    int extraBonus{0};        // +35,000 if this play crosses 63k on upper
    int shaping{0};           // path bonus / non-upper penalty (can be negative)
    bool immediateLower{false}; // (상대 전용) 이번 턴에 SS/LS/YACHT 즉시 성립 여부
    int effective() const { return score + extraBonus + shaping; }
};

// ==== Helpers for state ====
static int currentUpperSum(const GameState& st) {
    int s=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]!=-1) s+=st.ruleScore[r]; return s;
}
static int countUnusedUpper(const GameState& st) {
    int c=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]==-1) ++c; return c;
}
static int usedRulesCount(const GameState& st) {
    int c=0; for (int r=0; r<12; ++r) if (st.ruleScore[r]!=-1) ++c; return c;
}

// === Our evaluator (bonus-aware, with non-upper urgency penalty) ===
static EvalResult evaluateBestPlay(const GameState& st, const vector<int>& inventory) {
    EvalResult best; bool hasAny=false;
    int n = (int)inventory.size(); if (n < 5) return best;

    vector<array<int,5>> combs;
    if (n == 5) combs.push_back({0,1,2,3,4});
    else choose5Indices(n, combs);

    const int preUpper     = currentUpperSum(st);
    const int needUpper    = max(0, 63000 - preUpper);
    const int unusedUpper  = countUnusedUpper(st);
    const int scoredCount  = usedRulesCount(st);     // 0..12
    const double progress  = min(1.0, max(0.0, (double)scoredCount / 12.0));

    // Heuristic weights
    const double k_path   = 0.30;
    const double k_nonup  = 0.25;
    const double urg      = (unusedUpper <= 2 ? 1.0 : (0.4 + 0.6*progress));
    const double k_low    = 2500.0;               // ONE/TWO late small protection

    for (int r=0; r<12; ++r) {
        if (st.ruleScore[r] != -1) continue;
        for (auto id : combs) {
            vector<int> hand = { inventory[id[0]],inventory[id[1]],inventory[id[2]],
                                 inventory[id[3]],inventory[id[4]] };

            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0, shape = 0;

            if (r>=ONE && r<=SIX) {
                int post = preUpper + sc;
                if (preUpper < 63000 && post >= 63000) {
                    extra = 35000; // immediate crossing
                } else if (needUpper > 0) {
                    int reduce = min(sc, needUpper);
                    shape += (int)llround(k_path * reduce);
                }
                if ((r==ONE || r==TWO) && sc>0 && needUpper>0) {
                    double urg_low = (unusedUpper<=2 ? 1.0 : progress);
                    shape += (int)llround(k_low * urg_low);
                }
            } else {
                if (needUpper > 0 && unusedUpper > 0) {
                    int denom = max(1, unusedUpper);
                    int pen = (int)llround(k_nonup * urg * (double)needUpper / denom);
                    shape -= pen;
                }
            }

            if (!hasAny || sc + extra + shape > best.score + best.extraBonus + best.shaping) {
                best.rule = (DiceRule)r; best.dice = hand;
                best.score = sc; best.extraBonus = extra; best.shaping = shape; hasAny = true;
            }
        }
    }
    return best;
}

// === Opponent evaluator (분리):
//  - Non-upper penalty 미적용
//  - Upper path 보정 약화(k_path_opp)
//  - 즉시 하단 가중: SS +3000, LS +5000, YACHT +7000
static EvalResult evaluateBestPlay_Opp(const GameState& st, const vector<int>& inventory) {
    EvalResult best; bool hasAny=false;
    int n = (int)inventory.size(); if (n < 5) return best;

    vector<array<int,5>> combs;
    if (n == 5) combs.push_back({0,1,2,3,4});
    else choose5Indices(n, combs);

    const int preUpper     = currentUpperSum(st);
    const int needUpper    = max(0, 63000 - preUpper);
    const int scoredCount  = usedRulesCount(st);
    const double progress  = min(1.0, max(0.0, (double)scoredCount / 12.0));

    const double k_path_opp = 0.10;  // 약화된 upper path credit

    for (int r=0; r<12; ++r) {
        if (st.ruleScore[r] != -1) continue;
        for (auto id : combs) {
            vector<int> hand = { inventory[id[0]],inventory[id[1]],inventory[id[2]],
                                 inventory[id[3]],inventory[id[4]] };

            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0, shape = 0;
            bool immLower = false;

            if (r>=ONE && r<=SIX) {
                int post = preUpper + sc;
                if (preUpper < 63000 && post >= 63000) {
                    extra = 35000;
                } else if (needUpper > 0) {
                    int reduce = min(sc, needUpper);
                    shape += (int)llround(k_path_opp * reduce);
                }
            } else {
                if (sc > 0) {
                    if (r == SMALL_STRAIGHT)      { shape += 3000; immLower = true; }
                    else if (r == LARGE_STRAIGHT) { shape += 5000; immLower = true; }
                    else if (r == YACHT)          { shape += 7000; immLower = true; }
                }
            }

            if (!hasAny || sc + extra + shape > best.score + best.extraBonus + best.shaping) {
                best.rule = (DiceRule)r; best.dice = hand;
                best.score = sc; best.extraBonus = extra; best.shaping = shape;
                best.immediateLower = immLower; hasAny = true;
            }
        }
    }
    return best;
}

// Bundle value = best effective score this SCORE with (current5 + bundle5)
static int evaluateBundleValue(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    return evaluateBestPlay(st, merged).effective();
}

// Opp bundle value + immediate-lower flag
struct OppEvalPack {
    int effective{0};
    bool immLower{false};
    DiceRule rule{};
};
static OppEvalPack evaluateBundleValue_Opp(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    EvalResult er = evaluateBestPlay_Opp(st, merged);
    return { er.effective(), er.immediateLower, er.rule };
}

// ===== Game (bidding + scoring) =====
class Game {
public:
    GameState myState, oppState;

    int rollCount = 0;         // number of ROLLs seen (1..12)
    int seenOppBids = 0;       // GET events observed
    int oppNonZeroBids = 0;    // how many had amount > 0
    Bid lastMyBid{'A', 0};

    // ---- Bidding ----
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // 내 현재 시드(최대 5개만 평가에 사용)
        vector<int> mySeed = myState.dice;
        if ((int)mySeed.size() > 5) mySeed.resize(5);

        // 나의 번들 효용
        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);
        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // 두 번들 간 가치 차

        // 상대 선호(분리된 평가 사용)
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        OppEvalPack oA = evaluateBundleValue_Opp(oppState, oppSeed, diceA);
        OppEvalPack oB = evaluateBundleValue_Opp(oppState, oppSeed, diceB);
        char oppPref = (oA.effective > oB.effective) ? 'A' : 'B';
        bool oppImmLower = (oppPref=='A') ? oA.immLower : oB.immLower;
        DiceRule oppImmRule = (oppPref=='A') ? oA.rule : oB.rule;

        bool contested = (oppPref == myPref);

        // 진행도/점수차
        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // +면 내가 뒤지는 중
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // 상한: floor(0.5 * Δ)
        int cap = max(0, delta / 2);
        int amount = 0;

        // 상대 0-입찰 성향 추정
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80);

        // ===== Hard-deny 트리거 =====
        bool hardDeny = false;
        if (oppImmLower && (oppImmRule==SMALL_STRAIGHT || oppImmRule==LARGE_STRAIGHT || oppImmRule==YACHT)) {
            hardDeny = true;
            myPref = oppPref;    // 상대가 원하는 쪽을 우리가 경합
            contested = true;
        }

        // ===== 금액 계산 =====
        if (!contested || cap <= 0) {
            // 비경합 TAX: delta 기반 과세 + 바닥세
            double beta_tax = 0.25;           // Δ의 25% 정도만 세금처럼
            int taxCapEarly = 1000;           // 초반 최대 과세
            int taxCapLate  = 2000;           // 후반 최대 과세
            int taxCap = (int)llround(taxCapEarly + (taxCapLate - taxCapEarly) * progress);

            int taxBase = min(cap, (int)llround(beta_tax * (double)delta));
            amount = max(0, taxBase);

            // 바닥세: 최소 300 (단 cap 이내)
            int floorTax = min(300, taxCap);
            amount = max(amount, floorTax);
            amount = min(amount, cap);
        } else {
            if (oppLikelyZero) {
                // 타이브레이커 ε
                int eps = 7 + (rollCount * 13) % 23;
                amount = (eps <= cap) ? eps : 0;
            } else {
                // 비례입찰(상한 cap)
                double f = 0.20 + 0.25 * progress + min(0.15, max(0.0, scoreDiff / 100000.0));
                int base = (int)llround(delta * f);
                amount = min(cap, max(0, base));
                if (amount == 0) { int eps = 11; if (eps <= cap) amount = eps; }
            }

            // 경합 바닥세: cap>0 이면 ≥180
            if (cap > 0) amount = max(amount, min(180, cap));

            // Hard-deny 시 추가 하한: 초반~후반 900~2100
            if (hardDeny && cap > 0) {
                int minBid = min(cap, (int)llround(900 + 1200 * progress));
                amount = max(amount, minBid);
            }
        }

        amount = max(0, min(100000, amount));
        lastMyBid = Bid{ myPref, amount };
        return lastMyBid;
    }

    // ---- Scoring (bonus-aware full search) ----
    DicePut calculatePut() {
        EvalResult er = evaluateBestPlay(myState, myState.dice);
        if (er.dice.empty()) {
            // Fallback (거의 발생 X)
            int rule=-1; for (int i=0;i<12;++i) if (myState.ruleScore[i]==-1){rule=i;break;}
            vector<int> hand;
            for (int i=0;i<5 && i<(int)myState.dice.size(); ++i) hand.push_back(myState.dice[i]);
            while ((int)hand.size()<5 && !myState.dice.empty()) hand.push_back(myState.dice.back());
            return DicePut{ (DiceRule)rule, hand };
        }
        return DicePut{ er.rule, er.dice };
    }

    // ---- State updates ----
    void updateGet(const vector<int>& diceA, const vector<int>& diceB,
                   const Bid& myBid, const Bid& oppBid, char myGroup) {
        if (myGroup == 'A') { myState.addDice(diceA); oppState.addDice(diceB); }
        else                { myState.addDice(diceB); oppState.addDice(diceA); }

        bool myWon  = (myBid.group  == myGroup);
        bool oppWon = (oppBid.group == (myGroup=='A' ? 'B' : 'A'));
        myState.bid(myWon, myBid.amount);
        oppState.bid(oppWon, oppBid.amount);

        // 상대 입찰 통계 업데이트
        seenOppBids++;
        if (oppBid.amount > 0) oppNonZeroBids++;
    }

    void updatePut(const DicePut& put) { myState.useDice(put); }
    void updateSet(const DicePut& put) { oppState.useDice(put); }
};

// ===== Main (I/O protocol compatible with sample-code.cpp) =====
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
