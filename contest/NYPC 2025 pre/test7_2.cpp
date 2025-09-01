// 제출번호 82366: 6승 4패
// Yacht Auction AI (C++20, bonus-aware v3: defensive bidding + tax + aggressiveness)
// - I/O compatible with sample-code.cpp / test3.cpp
// - Changes from v2 (test3.cpp):
//   [Bidding]
//     (1) Defensive contest (deny): if opp's value gap is large, we can switch to contest even if our initial pref differs
//     (2) Non-contested tax: when we keep our pref (no contest), charge a "tax" proportional to opponent's gap
//     (3) Contest cap = floor(0.5 * (Δ_me + α * Δ_opp)); base factor f is higher when behind / late / opponent aggressive
//     (+) Opponent aggressiveness tracking: avg contested bid, high-bid rate; reflected in α and f
//   [Scoring]
//     - Upper-slot protection: apply late-game small positive boost to ANY upper rule (ONE..SIX) if sc>0
//     - Immediate lower exemption: when rule is LS/SS/YACHT and valid now, waive non-upper penalty
//
//   Tuning constants are grouped in struct Tuning at top.

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

// ===== Tuning knobs (single place to adjust) =====
struct Tuning {
    // Scoring heuristics
    double k_path   = 0.30;   // path bonus weight for upper-before-63k
    double k_nonup  = 0.25;   // non-upper penalty when upper still needed
    double k_low    = 2500.0; // small positive boost for any upper rule (ONE..SIX) if sc>0 late
    // Immediate lower exemption
    bool waivePenaltyForSS = true;
    bool waivePenaltyForLS = true;
    bool waivePenaltyForYacht = true;

    // Bidding (contest cap & factors)
    double alpha_cap     = 0.95;  // α in cap = 0.5 * (Δ_me + α * Δ_opp)
    double beta_oppon = 0.55;  // β for mixing Δ_opp into base amount: round((Δ_me + β*Δ_opp) * f)
    // Urgency vs score diff factor upper bound
    double f_scorediff_cap = 0.55; // was 0.15 in v2; increase to fight aggro
    // Non-contested "tax" when we don't contest
    double beta_tax      = 0.25;   // tax ~ β_tax * Δ_opp (clamped)
    int    taxCapEarly   = 1000;    // cap tax by stage
    int    taxCapLate    = 2000;

    // Defensive contest switch (deny)
    double theta_deny    = 0.75;    // thresholds dopp*U > theta * selfLoss
    // Aggressiveness thresholds
    int    highBidCut    = 1800;   // what counts as "high bid"
    double aggroRateTh   = 0.28;   // if rate of high bids among contested > this, they are aggressive
    int    aggroAvgCut   = 1500;   // or if avg contested bid > this
};

static Tuning K; // global tuning instance

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

    // Single-hand scoring for 5 dice (pure rule score)
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

// ===== Helpers for evaluator =====
static int currentUpperSum(const GameState& st) {
    int s=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]!=-1) s+=st.ruleScore[r]; return s;
}
static int countUnusedUpper(const GameState& st) {
    int c=0; for (int r=ONE; r<=SIX; ++r) if (st.ruleScore[r]==-1) ++c; return c;
}
static int usedRulesCount(const GameState& st) {
    int c=0; for (int r=0; r<12; ++r) if (st.ruleScore[r]!=-1) ++c; return c;
}

struct EvalResult {
    DiceRule rule{};
    vector<int> dice;
    int score{0};
    int extraBonus{0};        // +35,000 if this play crosses 63k on upper
    int shaping{0};           // path bonus / non-upper penalty (can be negative)
    int effective() const { return score + extraBonus + shaping; }
};

// === Bonus-aware evaluator (v3) ===
// Heuristics:
//  - Path bonus for upper:   k_path * min(sc, needed)
//  - Non-upper urgency penalty: -k_nonup * urgency * needed / max(1, unusedUpper)
//      * BUT waived when rule is SS/LS/YACHT and valid now (immediate lower exemption)
//  - Upper protection (extended): for ANY upper rule (ONE..SIX) if sc>0 and needUpper>0,
//      add k_low * urgency_low (late-game small boost to avoid 0 on upper slots)
static EvalResult evaluateBestPlay(const GameState& st, const vector<int>& inventory) {
    EvalResult best; bool hasAny=false;
    int n = (int)inventory.size(); if (n < 5) return best;

    // Precompute all 5-combinations of indices
    vector<array<int,5>> combs;
    if (n == 5) combs.push_back({0,1,2,3,4});
    else {
        array<int,5> idx{};
        auto dfs = [&](auto&& self, int i, int start) -> void {
            if (i == 5) { combs.push_back(idx); return; }
            for (int s = start; s <= n - (5 - i); ++s) {
                idx[i] = s; self(self, i+1, s+1);
            }
        };
        dfs(dfs, 0, 0);
    }

    const int preUpper     = currentUpperSum(st);
    const int needUpper    = max(0, 63000 - preUpper);
    const int unusedUpper  = countUnusedUpper(st);
    const int scoredCount  = usedRulesCount(st);     // 0..12
    const double progress  = min(1.0, max(0.0, (double)scoredCount / 12.0));
    const double urg       = (unusedUpper <= 2 ? 1.0 : (0.4 + 0.6*progress));

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
                    shape += (int)llround(K.k_path * reduce);
                }
                // Extended upper protection (ANY upper rule): if sc>0 and still need upper
                if (sc > 0 && needUpper > 0) {
                    double urg_low = (unusedUpper<=2 ? 1.0 : progress);
                    shape += (int)llround(K.k_low * urg_low);
                }
            } else {
                // Non-upper penalty only if we still need upper points
                if (needUpper > 0 && unusedUpper > 0) {
                    bool immediateLowerBig = false;
                    if (r == SMALL_STRAIGHT && K.waivePenaltyForSS && sc == 15000) immediateLowerBig = true;
                    if (r == LARGE_STRAIGHT && K.waivePenaltyForLS && sc == 30000) immediateLowerBig = true;
                    if (r == YACHT && K.waivePenaltyForYacht && sc == 50000) immediateLowerBig = true;

                    if (!immediateLowerBig) {
                        int denom = max(1, unusedUpper);
                        int pen = (int)llround(K.k_nonup * urg * (double)needUpper / denom);
                        shape -= pen;
                    }
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

    // Opponent aggressiveness stats (contested only)
    long long oppBidSumContested = 0;
    int       oppBidCntContested = 0;
    int       oppHighBidCntContested = 0;
    bool      lastContested = false; // set in calculateBid, consumed in updateGet
    int       lastOppBidAmount = 0;  // recorded in updateGet (for sanity)

    Bid lastMyBid{'A', 0};

    // ---- Helpers: seed dice for current 5 ----
    static vector<int> seed5(const vector<int>& inv) {
        vector<int> s = inv;
        if ((int)s.size() > 5) s.resize(5);
        return s;
    }

    // Urgency function for defensive contest
    static double denyUrgency(double progress, int upperLeft, bool haveBigLowerUnused, int scoreDiff) {
        // Base: progress (later -> higher)
        double u = 0.35 + 0.65 * progress;
        // Fewer upper slots left -> higher
        if (upperLeft <= 2) u += 0.25;
        // If LS/SS/YACHT still unused -> slightly higher (deny big swings)
        if (haveBigLowerUnused) u += 0.10;
        // If we're behind, more urgent (scaled by ~60k)
        u += min(0.35, max(0.0, (double)scoreDiff / 60000.0));
        return min(1.2, u);
    }

    // Aggressive opponent check
    bool isOppAggressive() const {
        double avg = (oppBidCntContested>0) ? (double)oppBidSumContested/oppBidCntContested : 0.0;
        double rate = (oppBidCntContested>0) ? (double)oppHighBidCntContested/oppBidCntContested : 0.0;
        return (avg > K.aggroAvgCut) || (rate > K.aggroRateTh);
    }

    // ---- Bidding ----
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // My & Opp "seed" dice (leftover after previous SCORE).
        vector<int> mySeed  = seed5(myState.dice);
        vector<int> oppSeed = seed5(oppState.dice);

        // Values for me
        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);
        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int dme     = myBest - myOther; // my value gap

        // Opponent preference & gap
        int oValA = evaluateBundleValue(oppState, oppSeed, diceA);
        int oValB = evaluateBundleValue(oppState, oppSeed, diceB);
        char oppPref = (oValA > oValB) ? 'A' : 'B';
        int dopp     = abs(oValA - oValB);

        bool contested = (oppPref == myPref);

        // Opponent zero-bid tendency (global)
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80);

        // Score deficit & progress
        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // positive if I'm behind
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // Big lower unused?
        auto used = myState.ruleScore;
        bool haveBigLowerUnused = (used[SMALL_STRAIGHT]==-1 || used[LARGE_STRAIGHT]==-1 || used[YACHT]==-1);

        // === (1) Defensive contest (deny) ===
        if (!contested) {
            // If opponent strongly wants their bundle, consider switching to contest
            int selfLoss = (myPref=='A' ? valA - valB : valB - valA); // loss if we switch
            int upperLeft = 0; for (int r=ONE; r<=SIX; ++r) if (myState.ruleScore[r]==-1) ++upperLeft;
            double U = denyUrgency(progress, upperLeft, haveBigLowerUnused, scoreDiff);
            if ((double)dopp * U > K.theta_deny * (double)max(0,selfLoss)) {
                myPref = oppPref; // switch to contest
                contested = true;
            }
        }

        // === Cap and base amount ===
        int cap = 0;
        int amount = 0;

        // Opp aggressiveness affects α and f
        bool oppAggro = isOppAggressive();
        double alpha = K.alpha_cap + (oppAggro ? 0.10 : 0.0); // be more willing to pay to cap
        alpha = min(1.0, alpha);

        if (contested) {
            // Cap = floor(0.5 * (Δ_me + α * Δ_opp))
            cap = max(0, (int)floor(0.5 * ( (double)dme + alpha * (double)dopp )));
            if (cap <= 0) {
                amount = 0;
            } else {
                if (oppLikelyZero) {
                    // small epsilon for tie-break
                    int eps = 7 + (rollCount * 13) % 23;
                    amount = (eps <= cap) ? eps : 0;
                } else {
                    // f: later & more behind & more aggressive opponent → higher
                    double f = 0.22 + 0.30 * progress
                               + min(K.f_scorediff_cap, max(0.0, (double)scoreDiff / 60000.0))
                               + (oppAggro ? 0.07 : 0.0);
                    f = min(0.60, f);
                    int base = (int)llround(((double)dme + K.beta_oppon * (double)dopp) * f);
                    amount = min(cap, max(0, base));
                    if (amount == 0) { int eps = 11; if (eps <= cap) amount = eps; }
                }
            }
        } else {
            // === (2) Non-contested "tax" ===
            int taxCap = (progress < 0.5 ? K.taxCapEarly : K.taxCapLate);
            int tax = (int)llround(K.beta_tax * (double)dopp);
            // small safety cap based on my own gaps to avoid bad EV
            int selfSafety = max(200, dme/3);
            int finalCap = min(taxCap, max(250, selfSafety));
            amount = max(0, min(finalCap, tax));
        }

        amount = max(0, min(100000, amount));
        lastMyBid = Bid{ myPref, amount };
        lastContested = contested;
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
        lastOppBidAmount = oppBid.amount;

        // Track aggressiveness only when last round was contested
        if (lastContested) {
            oppBidSumContested += oppBid.amount;
            oppBidCntContested += 1;
            if (oppBid.amount >= K.highBidCut) oppHighBidCntContested += 1;
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
