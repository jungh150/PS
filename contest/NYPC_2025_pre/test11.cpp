// 제출번호 82931: 6승 4패
// Yacht Auction AI (C++20) - Final merged version
// - sample-code.cpp 과 동일한 I/O 프로토콜 유지
// - 전략 요약:
//   [Bidding]
//     · 우리/상대 모두 현재 5개 시드 주사위 + 번들5 조합으로 이번 SCORE의 최고 효용을 평가
//     · 상대는 OppEval(상단 경로 보정 약화, 비상단 페널티 제거)로 추정
//     · 상대가 이번 턴에 SS/LS/YACHT를 바로 낼 수 있으면 Hard-Deny 게이트 통과 시 강제 경합 + 최소입찰 하한
//     · 비경합이면 소액 가드(초반 120, 후반 80)만, 경합이면 Δ비례 입찰(상대 0입찰러면 ε만)
//   [Scoring]
//     · 현재 인벤토리에서 5개를 뽑아 모든 rule에 대해 전탐색
//     · 상단 보너스(63,000→+35,000) 즉시 돌파 반영 + 상단 경로 보정(need를 줄이는 만큼 가점)
//     · 상단이 아직 필요할 때 비상단 선택엔 경미한 페널티
//     · 말미에 ONE/TWO가 양수면 소형 보호 가점(0점 방지)
//
//   * FULL_HOUSE는 3+2뿐 아니라 YACHT(5-kind)도 허용

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

// ===== Enum <-> String =====
static string toString(DiceRule rule) {
    switch (rule) {
        case ONE: return "ONE"; case TWO: return "TWO"; case THREE: return "THREE";
        case FOUR: return "FOUR"; case FIVE: return "FIVE"; case SIX: return "SIX";
        case CHOICE: return "CHOICE"; case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
        case FULL_HOUSE: return "FULL_HOUSE"; case SMALL_STRAIGHT: return "SMALL_STRAIGHT";
        case LARGE_STRAIGHT: return "LARGE_STRAIGHT"; case YACHT: return "YACHT";
    }
    assert(false); return "";
}
static DiceRule fromString(const string& s) {
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
    bool immediateLower{false}; // for opponent eval
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

// === Opponent evaluator:
//  - Non-upper penalty 미적용
//  - Upper path 보정 약화(k_path_opp)
//  - 즉시 하단(SS/LS/YACHT) 가능시 플래그 세팅
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

    const double k_path_opp = 0.10;  // weaker path credit

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
                    if (r == SMALL_STRAIGHT || r == LARGE_STRAIGHT || r == YACHT) immLower = true;
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

        // My current 5 "seed" dice (leftover after previous SCORE).
        vector<int> mySeed = myState.dice;
        if ((int)mySeed.size() > 5) mySeed.resize(5);

        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);
        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // value gap

        // Opponent preference using OppEval
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        OppEvalPack oA = evaluateBundleValue_Opp(oppState, oppSeed, diceA);
        OppEvalPack oB = evaluateBundleValue_Opp(oppState, oppSeed, diceB);
        char oppPref = (oA.effective > oB.effective) ? 'A' : 'B';
        bool oppImmLower = (oppPref=='A') ? oA.immLower : oB.immLower;
        DiceRule oppImmRule = (oppPref=='A') ? oA.rule : oB.rule;

        bool contested = (oppPref == myPref);

        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // positive if I'm behind
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        int cap = max(0, delta / 2);   // cap = floor(0.5 * Δ)
        int amount = 0;

        // 상대 0-입찰 성향 추정(초반 관측 적을 때 임계값 완화)
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (seenOppBids >= 2 ? oppZeroFrac >= 0.60 : oppZeroFrac >= 0.50);

        // Hard-deny 게이트 파라미터(완화 버전)
        int tau_deny  = (int)llround(600 + 1000 * progress);   // 600→1600
        int tau_delta = (int)llround(2000 + 3000 * progress);  // 2000→5000

        // Hard-deny 판단: 상대가 즉시 SS/LS/YACHT 가능하고, cap/Δ가 충분하며
        // 우리가 그 번들을 가져가도 가치가 너무 낮지 않을 때
        bool hardDeny = false;
        if (oppImmLower && (oppImmRule==SMALL_STRAIGHT || oppImmRule==LARGE_STRAIGHT || oppImmRule==YACHT)) {
            if (cap >= tau_deny && delta >= tau_delta) {
                int valOppPref = ((oA.effective > oB.effective) ? valA : valB);
                if (valOppPref >= (int)(0.3 * myBest)) { // 완화된 허들
                    hardDeny = true;
                    myPref = (oA.effective > oB.effective) ? 'A' : 'B';
                    contested = true;
                }
            }
        }

        if (!contested || cap <= 0) {
            // 비경합: 소액 가드만(초반 120, 후반 80). cap이 너무 작으면 0.
            if (cap >= 200) {
                int guard = (progress < 0.5) ? 120 : 80;
                amount = min(cap, guard);
            } else {
                amount = 0;
            }
        } else {
            // 경합
            if (oppLikelyZero) {
                // 타이브레이커용 ε(작은 소수점 패턴)
                int eps = 7 + (rollCount * 13) % 9; // 7~15
                amount = (eps <= cap) ? eps : 0;
            } else {
                // Δ 비례 + 진행도/점수열위 보정 (cap 이내)
                double f = 0.20 + 0.25 * progress + min(0.15, max(0.0, scoreDiff / 100000.0));
                if (progress < 0.4) f += 0.07; // 초반 경합 가중치
                int base = (int)llround(delta * f);
                amount = min(cap, max(0, base));
                if (amount == 0) { int eps = 11; if (eps <= cap) amount = eps; }
            }

            // Hard-deny면 완화된 하한 적용(초반~후반 600~1500)
            if (hardDeny && cap > 0) {
                int minBid = min(cap, (int)llround(600 + 900 * progress));
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
            // Fallback (이론상 거의 없음)
            int rule=-1; for (int i=0;i<12;++i) if (myState.ruleScore[i]==-1){rule=i;break;}
            vector<int> hand;
            for (int i=0;i<5 && i<(int)myState.dice.size(); ++i) hand.push_back(myState.dice[i]);
            while ((int)hand.size()<5 && !myState.dice.empty()) hand.push_back(myState.dice.back());
            return DicePut{ (DiceRule)rule, hand };
        }
        return DicePut{ er.rule, er.dice };
    }

    // ---- State updates (same protocol as sample) ----
    void updateGet(const vector<int>& diceA, const vector<int>& diceB,
                   const Bid& myBid, const Bid& oppBid, char myGroup) {
        if (myGroup == 'A') { myState.addDice(diceA); oppState.addDice(diceB); }
        else                { myState.addDice(diceB); oppState.addDice(diceA); }

        bool myWon  = (myBid.group  == myGroup);
        bool oppWon = (oppBid.group == (myGroup=='A' ? 'B' : 'A'));
        myState.bid(myWon, myBid.amount);
        oppState.bid(oppWon, oppBid.amount);

        // Opponent bid statistics
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
