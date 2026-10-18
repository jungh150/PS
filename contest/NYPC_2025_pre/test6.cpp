// 제출번호 82124: 3승 7패
// Yacht Auction AI (C++20) — v5
// Goal:
//  - Keep strong bonus-aware scoring for choosing rules
//  - FIX two root causes from logs:
//     (A) Never leave fragile rules (esp. FOUR_OF_A_KIND) to the very end
//         · If 4K is good now and rules left are few, take it now (positive shaping)
//         · If exactly 2 rules remain, DO NOT leave a fragile rule as the only leftover
//     (B) Stop overbidding caused by "path shaping" leaking into bid Δ
//         · Bid Δ uses ONLY (raw score + immediate-bonus), NOT shaping
//         · ABS_CAP = 4000, tighter scaling, small-Δ conservatism
//
// Other notes:
//  - FULL_HOUSE accepts both 3+2 and 5-kind(=YACHT)
//  - I/O protocol matches sample-code.cpp

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

// ===== Helpers =====
static int currentUpperSum(const GameState& st) {
    int s=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]!=-1) s+=st.ruleScore[r]; return s;
}
static int countUnusedUpper(const GameState& st) {
    int c=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]==-1) ++c; return c;
}
static int usedRulesCount(const GameState& st) {
    int c=0; for (int r=0; r<12; ++r) if (st.ruleScore[r]!=-1) ++c; return c;
}
static vector<int> listUnusedRules(const GameState& st) {
    vector<int> v; v.reserve(12);
    for (int r=0;r<12;++r) if (st.ruleScore[r]==-1) v.push_back(r);
    return v;
}
static bool isUpper(DiceRule r){ return r>=ONE && r<=SIX; }
static bool isFragile(DiceRule r){
    return r==FOUR_OF_A_KIND || r==FULL_HOUSE || r==SMALL_STRAIGHT || r==LARGE_STRAIGHT || r==YACHT;
}

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
    int score{0};           // raw score of chosen rule
    int extraBonus{0};      // +35,000 if this play crosses 63k on upper
    int shaping{0};         // path/penalties used ONLY for scoring decision
    int effective() const { return score + extraBonus + shaping; }
};

// === Bonus-aware evaluator (v5) ===
//  - Strong path shaping kept (as in v4) to improve bonus completion
//  - PLUS new fragile-rule scheduling:
//     * If rulesRemainingBefore <= 3 and (rule==4K) and sc>=22k → +10,000
//     * If exactly 2 rules unused BEFORE this play:
//         - If "other" remaining rule is fragile and we're NOT playing it now → −15,000
//         - If we ARE playing fragile now → +6,000 (small boost)
//     * Also small "+4,000" if rulesRemainingBefore <=3 and current rule is fragile with sc>0
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

    // v4 tuned weights (kept)
    const double K_path   = 0.90;
    const double K_nonup  = 0.40;
    const double urgency  = (unusedUpper <= 2 ? 1.15 : (0.5 + 0.6*progress));
    const double K_low    = 6500.0;
    const int DEADLINE_PENALTY = 10000;   // when unusedUpper ≤ 3
    const int THRESH_NEED = 12000;
    const int THRESH_BONUS = 8000;

    // Fragile scheduling params
    vector<int> unused = listUnusedRules(st);
    const int rulesRemainingBefore = (int)unused.size();
    const bool twoLeft = (rulesRemainingBefore == 2);
    int otherRule = -1;
    if (twoLeft) {
        // If exactly two rules are unused: the "other" is the one not chosen this turn.
        // We'll fill it after we decide r below.
        // For now, we just know there's exactly 2 candidates in 'unused'.
        // otherRule will be set per r in the loop.
    }

    for (int r=0; r<12; ++r) {
        if (st.ruleScore[r] != -1) continue;
        for (auto id : combs) {
            vector<int> hand = { inventory[id[0]],inventory[id[1]],inventory[id[2]],
                                 inventory[id[3]],inventory[id[4]] };

            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0, shape = 0;

            // --- Upper bonus shaping (same idea as v4) ---
            if (isUpper((DiceRule)r)) {
                int post = preUpper + sc;
                if (preUpper < 63000 && post >= 63000) {
                    extra = 35000; // immediate crossing
                } else if (needUpper > 0) {
                    int reduce = min(sc, needUpper);
                    shape += (int)llround(K_path * reduce);
                    int needAfter = max(0, 63000 - post);
                    if (needAfter <= THRESH_NEED) shape += THRESH_BONUS;
                }
                if (((DiceRule)r==ONE || (DiceRule)r==TWO) && sc>0 && needUpper>0) {
                    double urg_low = (unusedUpper<=2 ? 1.0 : progress);
                    shape += (int)llround(K_low * urg_low);
                }
            } else {
                if (needUpper > 0 && unusedUpper > 0) {
                    int denom = max(1, unusedUpper);
                    int pen = (int)llround(K_nonup * urgency * (double)needUpper / denom);
                    shape -= pen;
                    if (countUnusedUpper(st) <= 3) shape -= DEADLINE_PENALTY;
                }
            }

            // --- Fragile rule scheduling (new) ---
            // 1) Encourage taking FOUR_OF_A_KIND early when few rules remain and score is good
            if ((DiceRule)r == FOUR_OF_A_KIND && sc >= 22000 && rulesRemainingBefore <= 3) {
                shape += 10000;
            }
            // Small general encouragement for any fragile rule when few rules remain
            if (rulesRemainingBefore <= 3 && isFragile((DiceRule)r) && sc > 0) {
                shape += 4000;
            }
            // 2) If exactly two rules remain BEFORE this play:
            //    - penalize leaving a fragile rule as the final leftover
            //    - reward picking fragile now
            if (twoLeft) {
                // Find the "other" unused rule different from r
                int candidateOther = -1;
                if (unused.size()==2) {
                    candidateOther = (unused[0]==r ? unused[1] : (unused[1]==r ? unused[0] : -1));
                }
                if (candidateOther != -1) {
                    if (isFragile((DiceRule)candidateOther) && r != candidateOther) {
                        shape -= 15000; // don't leave fragile for last
                    }
                    if (isFragile((DiceRule)r)) {
                        shape += 6000;  // do pick fragile now
                    }
                }
            }

            // Choose best by effective()
            if (!hasAny || sc + extra + shape > best.score + best.extraBonus + best.shaping) {
                best.rule = (DiceRule)r; best.dice = hand;
                best.score = sc; best.extraBonus = extra; best.shaping = shape; hasAny = true;
            }
        }
    }
    return best;
}

// For bidding: compute immediate value = raw score + immediate upper-bonus (no shaping!)
static int immediateValueForBundle(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());

    // Evaluate immediate best: try all rules × all 5-combos but value = raw + immediate bonus only
    int n = (int)merged.size(); if (n < 5) return 0;

    vector<array<int,5>> combs;
    if (n == 5) combs.push_back({0,1,2,3,4});
    else choose5Indices(n, combs);

    const int preUpper = currentUpperSum(st);
    int best = 0;

    for (int r=0;r<12;++r) {
        if (st.ruleScore[r] != -1) continue;
        for (auto id : combs) {
            vector<int> hand = { merged[id[0]],merged[id[1]],merged[id[2]],merged[id[3]],merged[id[4]] };
            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0;
            if (isUpper((DiceRule)r)) {
                int post = preUpper + sc;
                if (preUpper < 63000 && post >= 63000) extra = 35000;
            }
            best = max(best, sc + extra);
        }
    }
    return best;
}

// Utility: compute q-quantile (0..1) from small vector of ints (copy-sort)
static int quantile(const vector<int>& v, double q) {
    if (v.empty()) return 0;
    vector<int> s = v; sort(s.begin(), s.end());
    int idx = (int)floor(q * (s.size() - 1));
    idx = max(0, min((int)s.size()-1, idx));
    return s[idx];
}

// ===== Game (bidding + scoring) =====
class Game {
public:
    GameState myState, oppState;

    int rollCount = 0;                    // number of ROLLs seen (1..12)
    int seenOppBids = 0;                  // GET events observed
    int oppNonZeroBids = 0;               // count of opponent bids > 0
    vector<int> oppContestedBids;         // opponent amounts in contested rounds (observed)
    Bid lastMyBid{'A', 0};

    // ---- Bidding (v5) ----
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // My current 5 "seed" dice (leftover after previous SCORE).
        vector<int> mySeed = myState.dice;
        if ((int)mySeed.size() > 5) mySeed.resize(5);

        // Immediate values for me (raw + immediate bonus only)
        int valA = immediateValueForBundle(myState, mySeed, diceA);
        int valB = immediateValueForBundle(myState, mySeed, diceB);

        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // value gap (immediate only)

        // Opponent preference by immediate value too
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        int oValA = immediateValueForBundle(oppState, oppSeed, diceA);
        int oValB = immediateValueForBundle(oppState, oppSeed, diceB);
        char oppPref = (oValA > oValB) ? 'A' : 'B';

        // Tighter contest margin (1500)
        const int CONTEST_MARGIN = 1500;
        bool contested = (oppPref == myPref) || (abs(oValA - oValB) < CONTEST_MARGIN);

        // Opponent zero-bid tendency (fast hard-zero: first 3 observed all zero)
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80);
        bool oppHardZero   = (seenOppBids >= 3 && oppNonZeroBids == 0);

        // Score deficit & progress
        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // + if I'm behind
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // Cap = min(floor(0.5 * Δ), ABS_CAP)
        int cap = max(0, delta / 2);
        const int ABS_CAP = 4000; // tighter
        cap = min(cap, ABS_CAP);

        int amount = 0;

        if (!contested || cap <= 0) {
            amount = 0;
        } else {
            if (oppHardZero) {
                amount = 0; // no drip spending vs true zero-bidder
            } else {
                // Opponent aggressiveness quantile (75%)
                int oppQ = quantile(oppContestedBids, 0.75);

                // Base proportional scaling (smaller than v4)
                double f = 0.15 + 0.20 * progress + min(0.15, max(0.0, (double)scoreDiff / 120000.0));
                int base = (int)llround(delta * f);

                // If opponent is mostly zero and oppQ==0 → still 0 (save points)
                if (oppLikelyZero && oppQ == 0) {
                    amount = 0;
                } else {
                    int want = max(base, oppQ + 1);
                    amount = min(cap, want);
                }

                // Small-Δ conservatism
                if (delta < 2000) amount = min(amount, delta / 4);
                if (delta < 1200) amount = 0; // don't bother
                amount = max(0, min(100000, amount));
            }
        }

        lastMyBid = Bid{ myPref, amount };
        return lastMyBid;
    }

    // ---- Scoring (bonus-aware full search + fragile scheduling) ----
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

        // Record opponent contested bid (observed): contested if we wanted same group
        if (myBid.group == oppBid.group) {
            oppContestedBids.push_back(oppBid.amount);
            if (oppContestedBids.size() > 64) { // keep memory bounded
                oppContestedBids.erase(oppContestedBids.begin());
            }
        }
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
