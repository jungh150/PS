// 제출번호 81695: 6승 4패
// Yacht Auction AI (C++20, bonus-aware v2)
// - Parsing & I/O are compatible with sample-code.cpp
// - Strategy:
//   * Bidding
//      - If we predict NON-CONTESTED (opponent wants the other bundle) → bid 0
//      - If CONTESTED → bid ≤ floor(0.5 * Δvalue)
//        · Opponent is likely zero-bidder → tiny ε only for tie-break
//        · Otherwise proportional to Δ, progress, and score deficit, but still ≤ 0.5Δ
//   * Scoring
//      - Every SCORE chooses the best (rule, 5-dice) by full search
//      - The evaluator is **bonus-aware**:
//          · Immediate bonus crossing (+35,000) is added
//          · Even if we don’t cross this turn, upper plays get a **path bonus**
//            proportional to how much they reduce the remaining distance to 63,000
//          · Non-upper plays get a small **urgency penalty** when we still need
//            upper points and few upper slots remain
//      - “ONE/TWO 보호”: late game에서 상단이 부족하면 낮은 눈(ONE/TWO)도 양수면
//        추가 가중치(소형 보정)를 부여하여 0점 방지
//
//   * Rules:
//      - FULL_HOUSE accepts both 3+2 **and** 5-of-a-kind(=YACHT) as valid
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
    int effective() const { return score + extraBonus + shaping; }
};

static int currentUpperSum(const GameState& st) {
    int s=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]!=-1) s+=st.ruleScore[r]; return s;
}
static int countUnusedUpper(const GameState& st) {
    int c=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]==-1) ++c; return c;
}
static int usedRulesCount(const GameState& st) {
    int c=0; for (int r=0; r<12; ++r) if (st.ruleScore[r]!=-1) ++c; return c;
}

// === Bonus-aware evaluator ===
// Heuristics:
//  - Path bonus for upper:   k_path * min(sc, needed)
//  - Non-upper urgency penalty: -k_nonup * urgency * needed / max(1, unusedUpper)
//  - Small “ONE/TWO” protection late: if rule is ONE/TWO and sc>0, add k_low * urgency_low
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

    // Heuristic weights (tunable)
    const double k_path   = 0.30;                 // progress-to-bonus credit for upper
    const double k_nonup  = 0.25;                 // penalty strength for non-upper when still need upper
    const double urg      = (unusedUpper <= 2 ? 1.0 : (0.4 + 0.6*progress)); // late-game urgency
    const double k_low    = 2500.0;               // small boost to ONE/TWO late to avoid 0

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
                    // Path credit: reduce the remaining distance
                    int reduce = min(sc, needUpper);
                    shape += (int)llround(k_path * reduce);
                }
                // ONE/TWO late small protection if we still need upper and score>0
                if ((r==ONE || r==TWO) && sc>0 && needUpper>0) {
                    double urg_low = (unusedUpper<=2 ? 1.0 : progress);
                    shape += (int)llround(k_low * urg_low);
                }
            } else {
                // Non-upper penalty only if we still need upper points
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

// Bundle value = best effective score this SCORE with (current5 + bundle5)
static int evaluateBundleValue(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    return evaluateBestPlay(st, merged).effective();
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

        // Values for me
        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);
        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // value gap

        // Opponent preference (rough)
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        int oValA = evaluateBundleValue(oppState, oppSeed, diceA);
        int oValB = evaluateBundleValue(oppState, oppSeed, diceB);
        char oppPref = (oValA > oValB) ? 'A' : 'B';

        bool contested = (oppPref == myPref);

        // Opponent zero-bid tendency
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80);

        // Score deficit & progress
        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // positive if I'm behind
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // Cap = floor(0.5 * Δ)
        int cap = max(0, delta / 2);
        int amount = 0;

        if (!contested || cap <= 0) {
            amount = 0;
        } else {
            if (oppLikelyZero) {
                // Tie-break ε
                int eps = 7 + (rollCount * 13) % 23;
                amount = (eps <= cap) ? eps : 0;
            } else {
                // Proportional bid with cap
                double f = 0.20 + 0.25 * progress + min(0.15, max(0.0, scoreDiff / 100000.0));
                int base = (int)llround(delta * f);
                amount = min(cap, max(0, base));
                if (amount == 0) { int eps = 11; if (eps <= cap) amount = eps; }
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
            // Defensive fallback (should not happen)
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
