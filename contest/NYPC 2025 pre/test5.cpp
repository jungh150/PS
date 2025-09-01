// 제출번호 82021: 5승 5패
// Yacht Auction AI (C++20)
// - Compatible I/O with sample-code.cpp
// - Changes from v3 (based on analysis vs #3/#4/#6/#7):
//   * MUCH stronger "upper-section bonus path" shaping so CHOICE/FULL 18~20k
//     won't consistently beat upper 9~12k when we still need the 63k bonus.
//       - K_path = 0.90
//       - Threshold booster: if post-upper need ≤ 12,000 → +8,000 shaping
//       - Non-upper deadline penalty when unusedUpper ≤ 3 (earlier than v3)
//       - ONE/TWO late protection: K_low = 6,500
//   * Bidding:
//       - Contest margin reduced (4,000 → 1,500)
//       - Fast zero-bid detection: first 3 rounds all 0 → treat opponent as hard-zero
//         → even on contested rounds, bid 0 (ε→0) to avoid useless drip spending
//       - Otherwise: ≤ floor(0.5 * Δ); quantile-beating; small Δ conservative
//   * FULL_HOUSE accepts 3+2 and 5-kind(=YACHT)
//
// Compile example:
//   g++ -std=c++20 -O2 -pipe -static -s main.cpp -o bot

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

// === Bonus-aware evaluator (v4 tuning) ===
//  - K_path = 0.90
//  - Threshold booster: if (preUpper<63k) and (postUpper need ≤ 12k) → +8,000 shaping
//  - Non-upper penalty stronger and earlier deadline: unusedUpper ≤ 3
//  - ONE/TWO late protection: K_low = 6,500
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

    // Tuned weights
    const double K_path   = 0.90;
    const double K_nonup  = 0.40;
    const double urgency  = (unusedUpper <= 2 ? 1.15 : (0.5 + 0.6*progress));
    const double K_low    = 6500.0;
    const int DEADLINE_PENALTY = 10000;   // applied when unusedUpper ≤ 3
    const int THRESH_NEED = 12000;        // post-need threshold
    const int THRESH_BONUS = 8000;        // shaping bump near the threshold

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
                    shape += (int)llround(K_path * reduce);
                    // If we're close to the threshold after this play, add a fixed bump
                    int needAfter = max(0, 63000 - post);
                    if (needAfter <= THRESH_NEED) shape += THRESH_BONUS;
                }
                // ONE/TWO late protection if we still need upper and score>0
                if ((r==ONE || r==TWO) && sc>0 && needUpper>0) {
                    double urg_low = (unusedUpper<=2 ? 1.0 : progress);
                    shape += (int)llround(K_low * urg_low);
                }
            } else {
                // Non-upper penalty only if we still need upper points
                if (needUpper > 0 && unusedUpper > 0) {
                    int denom = max(1, unusedUpper);
                    int pen = (int)llround(K_nonup * urgency * (double)needUpper / denom);
                    shape -= pen;
                    // Earlier deadline: when few upper slots left, penalize non-upper more
                    if (unusedUpper <= 3) shape -= DEADLINE_PENALTY;
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
static EvalResult evaluateBundleDetailed(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    return evaluateBestPlay(st, merged);
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

    // ---- Bidding (v4 tuning) ----
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // My current 5 "seed" dice (leftover after previous SCORE).
        vector<int> mySeed = myState.dice;
        if ((int)mySeed.size() > 5) mySeed.resize(5);

        // Evaluate both bundles for me
        int needMy = max(0, 63000 - currentUpperSum(myState));
        EvalResult erA = evaluateBundleDetailed(myState, mySeed, diceA);
        EvalResult erB = evaluateBundleDetailed(myState, mySeed, diceB);
        int valA = erA.effective();
        int valB = erB.effective();

        // Upper reduction for bonus-linked aggressiveness
        auto upperReduce = [&](const EvalResult& er)->int {
            if (needMy <= 0) return 0;
            bool isUpper = (er.rule>=ONE && er.rule<=SIX);
            return isUpper ? min(er.score, needMy) : 0;
        };
        int redA = upperReduce(erA);
        int redB = upperReduce(erB);

        char myPref = (valA > valB) ? 'A' : 'B';
        int myBest  = max(valA, valB);
        int myOther = min(valA, valB);
        int delta   = myBest - myOther; // value gap

        // Opponent preference (rough)
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) oppSeed.resize(5);
        EvalResult oerA = evaluateBundleDetailed(oppState, oppSeed, diceA);
        EvalResult oerB = evaluateBundleDetailed(oppState, oppSeed, diceB);
        int oValA = oerA.effective();
        int oValB = oerB.effective();
        char oppPref = (oValA > oValB) ? 'A' : 'B';

        // Margin-based contested prediction (tighter)
        const int CONTEST_MARGIN = 1500;
        bool contested = (oppPref == myPref) || (abs(oValA - oValB) < CONTEST_MARGIN);

        // Opponent zero-bid tendency
        double oppZeroFrac = 0.0;
        if (seenOppBids > 0) oppZeroFrac = double(seenOppBids - oppNonZeroBids) / double(seenOppBids);
        bool oppLikelyZero = (oppZeroFrac >= 0.80);
        // Fast hard-zero detection: first 3 rounds all zero → treat as hard-zero bidder
        bool oppHardZero = (seenOppBids >= 3 && oppNonZeroBids == 0);

        // Score deficit & progress
        int myTotal  = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // positive if I'm behind
        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1

        // Cap = floor(0.5 * Δ); absolute safety cap 10,000
        int cap = max(0, delta / 2);
        const int ABS_CAP = 10000;
        cap = min(cap, ABS_CAP);

        int amount = 0;

        if (!contested || cap <= 0) {
            amount = 0;
        } else {
            // If hard-zero, don't waste even ε
            if (oppHardZero) {
                amount = 0;
            } else {
                // Opponent aggressiveness quantile (70~80%)
                int oppQ = quantile(oppContestedBids, 0.75);

                // Base proportional part
                double f = 0.20 + 0.25 * progress + min(0.20, max(0.0, scoreDiff / 100000.0));
                // Extra boost if this bundle helps upper-path a lot (>= 6000)
                int myRed = (myPref=='A' ? redA : redB);
                if (myRed >= 6000) f += 0.20;

                int base = (int)llround(delta * f);

                if (oppLikelyZero && oppQ == 0) {
                    // In v4, ε → 0 to avoid drip spending against true zero-bidders
                    amount = 0;
                } else {
                    // Bid to beat typical opponent bid OR proportional, within cap
                    int want = max(base, oppQ + 1);
                    amount = min(cap, want);
                }

                // If Δ is small, be conservative
                if (delta < 1800) amount = min(amount, delta / 3);
                amount = max(0, min(100000, amount));
            }
        }

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
