// 제출번호 81485: 3승 7패
// Yacht Auction AI (C++20)
// - Uses the same I/O & parsing style as the provided sample-code.cpp
// - Implements a value-driven bidding & scoring strategy:
//    * Bid on the bundle (A/B) that maximizes immediate scoring value with current inventory
//    * Bid amount scales with value gap, round progress, and score deficit
//    * For scoring, do full search over all 5-dice subsets (≤ C(10,5)=252) × remaining rules
//    * Upper-section bonus (63,000 → +35,000) is explicitly valued during selection
//    * Opponent preference is estimated to boost bid when we expect contention
//
// NOTE:
//  - FULL_HOUSE follows the strict rule: exactly 3-of-a-kind + exactly 2-of-a-kind (5-kind is NOT full house)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <optional>
#include <cmath>
#include <functional>

using namespace std;

// ===== Rules =====
enum DiceRule {
    ONE, TWO, THREE, FOUR, FIVE, SIX,               // 0..5 (upper section)
    CHOICE, FOUR_OF_A_KIND, FULL_HOUSE,             // 6..8
    SMALL_STRAIGHT, LARGE_STRAIGHT, YACHT           // 9..11
};

// ===== Bid & Put =====
struct Bid {
    char group; // 'A' or 'B'
    int amount; // 0..100000
};

struct DicePut {
    DiceRule rule;
    vector<int> dice; // exactly 5 dice (values in [1..6])
};

// ===== Helper: enum-string conversion =====
string toString(DiceRule rule) {
    switch (rule) {
        case ONE: return "ONE";
        case TWO: return "TWO";
        case THREE: return "THREE";
        case FOUR: return "FOUR";
        case FIVE: return "FIVE";
        case SIX: return "SIX";
        case CHOICE: return "CHOICE";
        case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
        case FULL_HOUSE: return "FULL_HOUSE";
        case SMALL_STRAIGHT: return "SMALL_STRAIGHT";
        case LARGE_STRAIGHT: return "LARGE_STRAIGHT";
        case YACHT: return "YACHT";
    }
    assert(!"Invalid Dice Rule");
    return "";
}

DiceRule fromString(const string& s) {
    if (s == "ONE") return ONE;
    if (s == "TWO") return TWO;
    if (s == "THREE") return THREE;
    if (s == "FOUR") return FOUR;
    if (s == "FIVE") return FIVE;
    if (s == "SIX") return SIX;
    if (s == "CHOICE") return CHOICE;
    if (s == "FOUR_OF_A_KIND") return FOUR_OF_A_KIND;
    if (s == "FULL_HOUSE") return FULL_HOUSE;
    if (s == "SMALL_STRAIGHT") return SMALL_STRAIGHT;
    if (s == "LARGE_STRAIGHT") return LARGE_STRAIGHT;
    if (s == "YACHT") return YACHT;
    assert(!"Invalid Dice Rule");
    return ONE; // unreachable
}

// ===== GameState =====
struct GameState {
    vector<int> dice;          // current inventory (values 1..6)
    vector<int> ruleScore;     // per rule: scored points, -1 if unused
    int bidScore;              // cumulative (win bid → minus, lose bid → plus)

    GameState() : ruleScore(12, -1), bidScore(0) {}

    // ----- Public API -----
    int getTotalScore() const {
        int upper = 0, lower = 0, bonus = 0;
        for (int i = 0; i < 6; ++i) if (ruleScore[i] != -1) upper += ruleScore[i];
        if (upper >= 63000) bonus = 35000;
        for (int i = 6; i < 12; ++i) if (ruleScore[i] != -1) lower += ruleScore[i];
        return upper + bonus + lower + bidScore;
    }

    void bid(bool won, int amount) {
        if (won) bidScore -= amount; else bidScore += amount;
    }

    void addDice(const vector<int>& nd) {
        dice.insert(dice.end(), nd.begin(), nd.end());
    }

    void useDice(const DicePut& put) {
        // rule unused?
        assert(ruleScore[put.rule] == -1 && "Rule already used");
        // remove used dice (by value, one by one)
        vector<int> pool = dice;
        for (int v : put.dice) {
            auto it = find(pool.begin(), pool.end(), v);
            assert(it != pool.end() && "Invalid dice used");
            pool.erase(it);
        }
        dice.swap(pool);
        // store score
        ruleScore[put.rule] = calculateScoreStatic(put.rule, put.dice);
    }

    // ----- Static: scoring core for a 5-dice hand -----
    static int calculateScoreStatic(DiceRule rule, const vector<int>& dice) {
        // counts of faces 1..6
        array<int, 7> cnt{}; // 0 unused
        for (int d : dice) cnt[d]++;

        auto sumAll = accumulate(dice.begin(), dice.end(), 0) * 1000;

        switch (rule) {
            case ONE:   return cnt[1] * 1 * 1000;
            case TWO:   return cnt[2] * 2 * 1000;
            case THREE: return cnt[3] * 3 * 1000;
            case FOUR:  return cnt[4] * 4 * 1000;
            case FIVE:  return cnt[5] * 5 * 1000;
            case SIX:   return cnt[6] * 6 * 1000;

            case CHOICE:
                return sumAll;

            case FOUR_OF_A_KIND: {
                bool ok = false;
                for (int v = 1; v <= 6; ++v) if (cnt[v] >= 4) { ok = true; break; }
                return ok ? sumAll : 0;
            }

            case FULL_HOUSE: {
                // strict: exactly 3-of-a-kind + exactly 2-of-a-kind (5-kind NOT allowed)
                bool has3 = false, has2 = false;
                for (int v = 1; v <= 6; ++v) {
                    if (cnt[v] == 3) has3 = true;
                    if (cnt[v] == 2) has2 = true;
                }
                return (has3 && has2) ? sumAll : 0;
            }

            case SMALL_STRAIGHT: {
                // presence-only check for (1234) or (2345) or (3456)
                auto has = [&](int v){ return cnt[v] > 0; };
                bool ok = (has(1)&&has(2)&&has(3)&&has(4)) ||
                          (has(2)&&has(3)&&has(4)&&has(5)) ||
                          (has(3)&&has(4)&&has(5)&&has(6));
                return ok ? 15000 : 0;
            }

            case LARGE_STRAIGHT: {
                auto has = [&](int v){ return cnt[v] > 0; };
                bool ok = (has(1)&&has(2)&&has(3)&&has(4)&&has(5)) ||
                          (has(2)&&has(3)&&has(4)&&has(5)&&has(6));
                return ok ? 30000 : 0;
            }

            case YACHT: {
                for (int v = 1; v <= 6; ++v) if (cnt[v] == 5) return 50000;
                return 0;
            }
        }
        assert(false);
        return 0;
    }
};

// ===== Combinatorics: generate all 5-combinations of an array =====
static void choose5Indices(int n, vector<array<int,5>>& out) {
    // n ≤ 10 → at most C(10,5)=252 combos
    array<int,5> idx{};
    function<void(int,int)> dfs = [&](int i, int start){
        if (i == 5) { out.push_back(idx); return; }
        for (int s = start; s <= n - (5 - i); ++s) { idx[i] = s; dfs(i+1, s+1); }
    };
    dfs(0, 0);
}

// ===== Value evaluator for a given inventory =====
struct EvalResult {
    DiceRule rule;
    vector<int> dice; // 5 dice chosen
    int score;        // immediate rule score (w/o bid)
    int extraBonus;   // +35000 if this play crosses 63k upper threshold, else 0
    int effective() const { return score + extraBonus; }
};

// Computes the upper-section sum already taken (ONE..SIX) in the given state
static int currentUpperSum(const GameState& st) {
    int s = 0;
    for (int r = ONE; r <= SIX; ++r) if (st.ruleScore[r] != -1) s += st.ruleScore[r];
    return s;
}

// Evaluate the best immediate play (rule + 5-dice selection) on the given inventory
static EvalResult evaluateBestPlay(const GameState& st, const vector<int>& inventory) {
    // Precompute 5-combinations of indices
    EvalResult best{ONE, {}, 0, 0};
    bool hasAny = false;

    vector<array<int,5>> combs;
    int n = (int)inventory.size();
    if (n < 5) return best; // shouldn't happen in normal SCORE phases except early (engine-specific)
    if (n == 5) {
        combs.push_back({0,1,2,3,4});
    } else {
        choose5Indices(n, combs);
    }

    // Cache upper sum for bonus check
    const int preUpper = currentUpperSum(st);

    // For all unused rules
    for (int r = 0; r < 12; ++r) {
        if (st.ruleScore[r] != -1) continue; // already used

        for (auto idx5 : combs) {
            vector<int> hand = { inventory[idx5[0]], inventory[idx5[1]],
                                 inventory[idx5[2]], inventory[idx5[3]],
                                 inventory[idx5[4]] };

            int sc = GameState::calculateScoreStatic((DiceRule)r, hand);
            int extra = 0;
            if (r >= ONE && r <= SIX) {
                int postUpper = preUpper + sc;
                if (preUpper < 63000 && postUpper >= 63000) extra = 35000;
            }

            if (!hasAny || sc + extra > best.score + best.extraBonus) {
                best.rule = (DiceRule)r;
                best.dice = hand;
                best.score = sc;
                best.extraBonus = extra;
                hasAny = true;
            }
        }
    }

    if (!hasAny) {
        // Fallback: no rules left? (should not happen before FINISH)
        best = EvalResult{ONE, {}, 0, 0};
    }
    return best;
}

// Evaluate the "value" of adding a candidate bundle to current inventory
// We define value as the best immediate effective score we could achieve this SCORE phase.
static int evaluateBundleValue(const GameState& st, const vector<int>& current5, const vector<int>& bundle5) {
    vector<int> merged = current5;
    merged.insert(merged.end(), bundle5.begin(), bundle5.end());
    EvalResult er = evaluateBestPlay(st, merged);
    return er.effective(); // score + potential +35k if crossing upper threshold
}

// ===== Game engine with strategy =====
class Game {
public:
    GameState myState, oppState;

    // Track progress for bidding aggressiveness
    int rollCount = 0;     // number of ROLLs observed (max 12, since 13th has no ROLL)
    // We also track last opponent bid to update
    Bid lastMyBid{'A', 0};

    // ----- Strategy: Bidding -----
    Bid calculateBid(const vector<int>& diceA, const vector<int>& diceB) {
        rollCount++;

        // Extract my current "seed" (normally 5 dice except very early)
        vector<int> mySeed = myState.dice; // whatever remains from previous SCORE
        // Often 5 (after SCORE), but can be 0 for the very first ROLL.

        // If we have more than 5 (shouldn't before SCORE), just consider the last 5 as seed.
        if ((int)mySeed.size() > 5) {
            // Keep higher-sum 5 as a rough heuristic
            // (Defensive guard; in the official flow this shouldn't be needed.)
            sort(mySeed.begin(), mySeed.end(), greater<>());
            mySeed.resize(5);
        }

        // My value estimate for each bundle
        int valA = evaluateBundleValue(myState, mySeed, diceA);
        int valB = evaluateBundleValue(myState, mySeed, diceB);

        // Opponent value estimate (for contention prediction)
        vector<int> oppSeed = oppState.dice;
        if ((int)oppSeed.size() > 5) {
            sort(oppSeed.begin(), oppSeed.end(), greater<>());
            oppSeed.resize(5);
        }
        int oValA = evaluateBundleValue(oppState, oppSeed, diceA);
        int oValB = evaluateBundleValue(oppState, oppSeed, diceB);

        // Choose group with larger value (tie → B as in sample’s implicit behavior)
        char group = (valA > valB) ? 'A' : 'B';
        int myBest = max(valA, valB);
        int myOther = min(valA, valB);
        int delta = myBest - myOther; // value gap

        // Predict contention: opponent likely prefers the same group?
        char oppPref = (oValA > oValB) ? 'A' : 'B';
        bool contested = (oppPref == group);

        // Amount decision:
        // base on value gap, round progress, score deficit, and contention
        int myTotal = myState.getTotalScore();
        int oppTotal = oppState.getTotalScore();
        int scoreDiff = oppTotal - myTotal; // positive if I'm behind

        double progress = min(1.0, max(0.0, (rollCount - 1) / 11.0)); // 0..1 over 12 bidding rounds
        double k_base = 0.35;                 // base conversion ratio (value → bid)
        double k_prog = 0.8 + 0.4 * progress; // later → a bit more aggressive (0.8..1.2)
        double k_def  = 1.0 + min(1.0, max(0.0, scoreDiff / 50000.0)); // behind → up to ×2.0
        double k_cont = contested ? 1.15 : 1.0; // contention boost

        int amount = 0;
        if (delta > 0) {
            double raw = delta * k_base * k_prog * k_def * k_cont;

            // Soft floor when hotly contested
            if (contested) {
                raw = max(raw, delta * 0.15); // ensure we don’t lose on tiny rounding
                raw = max(raw, 200.0);        // small constant nudge
            }

            // Avoid micro-bids when value gap is tiny
            if (delta < 2000) raw = min(raw, (double)delta * 0.25);

            amount = (int)llround(raw);
        }

        // Clamp to [0, 100000]
        amount = max(0, min(100000, amount));

        lastMyBid = Bid{group, amount};
        return lastMyBid;
    }

    // ----- Strategy: Scoring (PUT) -----
    DicePut calculatePut() {
        // Build best play on current inventory (10 dice usually, 5 dice in last SCORE)
        EvalResult er = evaluateBestPlay(myState, myState.dice);

        // Tie-breakers (lightweight): if multiple same effective, prefer:
        //  - upper rules when close to bonus; else higher raw score
        // Already handled by effective() = score + bonus bump.

        // Safety: if empty (shouldn’t happen), default to first unused rule + first 5 dice
        if (er.dice.empty()) {
            int rule = -1;
            for (int i = 0; i < 12; ++i) if (myState.ruleScore[i] == -1) { rule = i; break; }
            vector<int> hand;
            for (int i = 0; i < 5 && i < (int)myState.dice.size(); ++i) hand.push_back(myState.dice[i]);
            if (hand.size() < 5) { // pad (defensive)
                while ((int)hand.size() < 5 && !myState.dice.empty()) hand.push_back(myState.dice.back());
            }
            return DicePut{ (DiceRule)rule, hand };
        }

        return DicePut{ er.rule, er.dice };
    }

    // ===== State updates (same semantics as the sample) =====
    void updateGet(const vector<int>& diceA, const vector<int>& diceB,
                   const Bid& myBid, const Bid& oppBid, char myGroup) {
        // distribute bundles
        if (myGroup == 'A') { myState.addDice(diceA); oppState.addDice(diceB); }
        else                { myState.addDice(diceB); oppState.addDice(diceA); }

        // bid outcomes
        bool myWon  = (myBid.group  == myGroup);
        bool oppWon = (oppBid.group == (myGroup == 'A' ? 'B' : 'A'));
        myState.bid(myWon,  myBid.amount);
        oppState.bid(oppWon, oppBid.amount);
    }

    void updatePut(const DicePut& put)  { myState.useDice(put); }
    void updateSet(const DicePut& put)  { oppState.useDice(put); }
};

// ===== Main (I/O protocol compatible with sample) =====
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
        string command;
        iss >> command;

        if (command == "READY") {
            cout << "OK\n";
            cout.flush();
        }
        else if (command == "ROLL") {
            string strA, strB;
            iss >> strA >> strB;
            diceA.clear(); diceB.clear();
            for (char c : strA) diceA.push_back(c - '0');
            for (char c : strB) diceB.push_back(c - '0');

            myBid = game.calculateBid(diceA, diceB);
            cout << "BID " << myBid.group << " " << myBid.amount << "\n";
            cout.flush();
        }
        else if (command == "GET") {
            char myGroup, oppGroup;
            int oppScore;
            iss >> myGroup >> oppGroup >> oppScore;
            game.updateGet(diceA, diceB, myBid, Bid{oppGroup, oppScore}, myGroup);
        }
        else if (command == "SCORE") {
            DicePut put = game.calculatePut();
            game.updatePut(put);
            cout << "PUT " << toString(put.rule) << " ";
            for (int d : put.dice) cout << d;
            cout << "\n";
            cout.flush();
        }
        else if (command == "SET") {
            string ruleStr, str;
            iss >> ruleStr >> str;
            vector<int> d;
            for (char c : str) d.push_back(c - '0');
            game.updateSet(DicePut{ fromString(ruleStr), d });
        }
        else if (command == "FINISH") {
            break;
        }
        else {
            // Unknown command → ignore or report
            // cerr << "Invalid command: " << command << "\n";
            // return 1;
        }
    }

    return 0;
}
