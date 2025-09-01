#include <bits/stdc++.h>
using namespace std;

auto gen_rand = [](int l, int r) {
    static mt19937 rd(0x814814);
    return uniform_int_distribution(l, r)(rd);
};

string get_op_name(int op) {
    if (op == 0) return "ONE";
    if (op == 1) return "TWO";
    if (op == 2) return "THREE";
    if (op == 3) return "FOUR";
    if (op == 4) return "FIVE";
    if (op == 5) return "SIX";
    if (op == 6) return "CHOICE";
    if (op == 7) return "FOUR_OF_A_KIND";
    if (op == 8) return "FULL_HOUSE";
    if (op == 9) return "SMALL_STRAIGHT";
    if (op == 10) return "LARGE_STRAIGHT";
    if (op == 11) return "YACHT";
    return "UNKNOWN";
}

static bool is_small_straight_str(const string& s) {
    int mask = 0; for (char ch : s) mask |= 1 << (ch - '1');
    return ((mask & 15) == 15) || (((mask >> 1) & 15) == 15) || (((mask >> 2) & 15) == 15);
}
static bool is_large_straight_str(const string& s) {
    int mask = 0; for (char ch : s) mask |= 1 << (ch - '1');
    return ((mask & 31) == 31) || (((mask >> 1) & 31) == 31);
}
static bool is_any_straight_str(const string& s) { return is_small_straight_str(s) || is_large_straight_str(s); }

static int deck56score_by_cnt_sum(int c5, int c6, int sum) {
    return 400 * c6 + 250 * c5 + sum;
}

struct board {
    board() : used_mask(0), score_up(0), score_down(0) { memset(cnt,0,sizeof(cnt)); }
    void roll(string a, string b) { prv_a = a; prv_b = b; }
    void get(int type) { if (type == 0) update(prv_a, +1); else update(prv_b, +1); }
    void put(int op, string s) {
        used_mask |= 1 << op;
        update(s, -1);
        if (op <= 5) score_up += calc(op, s);
        else score_down += calc(op, s);
    }

    array<int,7> get_cnt() const { array<int,7> a{}; for (int i=1;i<=6;i++) a[i]=cnt[i]; return a; }
    bool rule_used(int op) const { return (used_mask >> op) & 1; }

    auto choose_greedy() {
        int ret_op = -1; string ret_s; int ret_val = -1;
        auto rec = [&](const auto& self, int dep, string acc) -> void {
            if (dep == 7) {
                if ((int)acc.size() != 5) return;
                for (int op = 0; op <= 11; op++) {
                    if ((used_mask >> op) & 1) continue;
                    int val = calc(op, acc);
                    if (ret_val >= val) continue;
                    ret_op = op; ret_s = acc; ret_val = val;
                }
                return;
            }
            for (int i=0;i<=cnt[dep];i++) { self(self, dep+1, acc); acc.push_back(dep+'0'); if ((int)acc.size()>5) break; }
        };
        rec(rec, 1, string{});
        return pair(ret_op, ret_s);
    }

    auto choose() {
        if (~used_mask >> 11 & 1 && cnt[1] == 5) return pair(11, string("11111"));
        if (~used_mask >> 11 & 1 && cnt[2] == 5) return pair(11, string("22222"));
        if (~used_mask >> 11 & 1 && cnt[3] == 5) return pair(11, string("33333"));

        if (~used_mask >> 5 & 1 && cnt[6] >= 5) return pair(5, string("66666"));
        if (~used_mask >> 5 & 1 && cnt[6] == 4) {
            int p=1; while (cnt[p]==0) p++;
            return pair(5, string("6666")+char(p+'0'));
        }
        if (~used_mask >> 4 & 1 && cnt[5] == 5) return pair(4, string("55555"));

        struct Cand { int op; string s; int eff; bool isUpper; };
        Cand bestU{-1,"",-1000000000,true}, bestL{-1,"",-1000000000,false};

        int round = __builtin_popcount((unsigned)used_mask);
        int unusedUpper = 0; for (int i=0;i<=5;i++) if (((used_mask>>i)&1)==0) unusedUpper++;
        int needUpper = max(0, 63000 - score_up);

        bool five_unused = ((used_mask>>4)&1)==0;
        bool six_unused  = ((used_mask>>5)&1)==0;

        auto rec = [&](const auto& self, int dep, string acc)->void{
            if (dep==7) {
                if ((int)acc.size()!=5) return;

                int a[7]{}; for (char ch: acc) a[ch-'0']++;
                int c1=a[1], c2=a[2], c3=a[3], c4=a[4], c5=a[5], c6=a[6];
                int use56 = c5 + c6;

                for (int op=0; op<=11; op++) {
                    if ((used_mask>>op)&1) continue;

                    int sc = calc(op, acc);
                    int val = sc;
                    bool isUpper = (op<=5);

                    if (op==0 && c1==0) val = -1000000000;
                    if (op==1 && c2==0) val = -1000000000;
                    if (op==2 && c3==0) val = -1000000000;

                    if ((op==0||op==1||op==2) && sc>0 && needUpper>0 && unusedUpper<=3) val += 7000;

                    if (op==3 && c4<=1 && needUpper>0) val -= 6000;

                    if (op==4 && c5<=2 && five_unused)  val -= 20000;
                    if (op==5 && c6<=2 && six_unused)   val -= 30000;

                    if (op==6 && round<=4) val -= 40000;
                    if (op==6 && (five_unused || six_unused)) {
                        val -= 4000*c5 + 6000*c6;
                    }

                    if (op==9 || op==10) {
                        bool early = (round<=3);
                        if (use56==0)       val += early ? 4000 : 2500;
                        else {
                            if (five_unused) val -= 2000*c5;
                            if (six_unused)  val -= 3500*c6;
                        }
                    }

                    if (op>5 && (five_unused || six_unused)) {
                        val -= 5000*c5 + 7000*c6;
                    }

                    if (op>5 && needUpper>0 && unusedUpper>0) {
                        int pen = (int)llround(0.35 * (double)needUpper / max(1, unusedUpper));
                        val -= pen;
                    }

                    {
                        update(acc, -1);  used_mask ^= 1<<op;
                        int sum=0, trials=3;
                        for (int iter=0; iter<trials; iter++) {
                            string t; for (int i=0;i<5;i++) t.push_back(gen_rand(1,6)+'0');
                            update(t, +1);
                            auto [nop, ns] = choose_greedy();
                            sum += calc(nop, ns);
                            update(t, -1);
                        }
                        val += (sum / trials) / 5;
                        update(acc, +1);  used_mask ^= 1<<op;
                    }

                    if (isUpper) {
                        if (val > bestU.eff) bestU = Cand{op, acc, val, true};
                    } else {
                        if (val > bestL.eff) bestL = Cand{op, acc, val, false};
                    }
                }
                return;
            }
            for (int i=0;i<=cnt[dep];i++) { self(self, dep+1, acc); acc.push_back(dep+'0'); if ((int)acc.size()>5) break; }
        };
        rec(rec, 1, string{});

        if (needUpper > 0) {
            int M = (int)llround(0.35 * needUpper + 2500.0 * (double)unusedUpper + 7000.0);
            if (bestU.op != -1 && (bestL.op == -1 || bestL.eff < bestU.eff + M)) {
                return pair(bestU.op, bestU.s);
            } else if (bestL.op != -1) {
                return pair(bestL.op, bestL.s);
            }
        } else {
            if (bestU.op != -1 && (bestL.op == -1 || bestU.eff >= bestL.eff)) {
                return pair(bestU.op, bestU.s);
            } else if (bestL.op != -1) {
                return pair(bestL.op, bestL.s);
            }
        }

        int fallback_op=-1; string fallback_s; int best=-1000000000;
        auto rec2 = [&](const auto& self, int dep, string acc)->void{
            if (dep==7) {
                if ((int)acc.size()!=5) return;
                for (int op=0; op<=11; op++) {
                    if ((used_mask>>op)&1) continue;
                    int v = calc(op, acc);
                    if (v > best) { best=v; fallback_op=op; fallback_s=acc; }
                }
                return;
            }
            for (int i=0;i<=cnt[dep];i++) { self(self, dep+1, acc); acc.push_back(dep+'0'); if ((int)acc.size()>5) break; }
        };
        rec2(rec2, 1, string{});
        return pair(fallback_op, fallback_s);
    }

    int get_score() const { return score_up + score_down; }

private:
    int used_mask;
    int cnt[7];
    int score_up;
    int score_down;
    string prv_a, prv_b;

    void update(const string& s, int x) { for (char ch: s) cnt[ch-'0'] += x; }

    int calc(int op, const string& s) const {
        int a[7]{}, b[6]{}; int sum=0, mask=0;
        for (char ch: s) { int v=ch-'0'; a[v]++; sum+=v; mask |= 1<<(v-1); }
        for (int i=1;i<=6;i++) b[a[i]]++;

        if (op==6)  return sum*1000;
        if (op==7)  return (b[4]||b[5]) ? sum*1000 : 0;
        if (op==8)  return ((b[2]&&b[3])||b[5]) ? sum*1000 : 0;
        if (op==9)  return (((mask&15)==15)||(((mask>>1)&15)==15)||(((mask>>2)&15)==15)) ? 15000 : 0;
        if (op==10) return (((mask&31)==31)||(((mask>>1)&31)==31)) ? 30000 : 0;
        if (op==11) return b[5] ? 50000 : 0;

        int face = op+1;
        int val = a[face] * face * 1000;
        if (score_up < 63000 && score_up + val >= 63000) val += 35000;
        return val;
    }
};

static array<int,7> str_cnt(const string& s) { array<int,7> c{}; for (char ch: s) c[ch-'0']++; return c; }

int opp_zero_cnt = 0;
int opp_seen_cnt = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    board f, g;
    int f_score_bid=0, g_score_bid=0;
    int f_prv_type=0, f_prv_bid=0, g_prv_bid=0;

    while (true) {
        string input; if(!getline(cin, input)) break;
        if (input.empty()) continue;
        istringstream in(input);
        string cmd; in >> cmd;

        if (cmd=="READY") {
            cout << "OK" << endl;
        }
        else if (cmd=="ROLL") {
            string a,b; in >> a >> b;

            int sa=0,sb=0; for(char ch: a) sa+=ch-'0'; for(char ch: b) sb+=ch-'0';

            int f_score = f_score_bid + f.get_score();
            int g_score = g_score_bid + g.get_score();
            int val = (f_score - g_score) / 10;
            if (val < 0) val = 0;
            if (val > 100000) val = 100000;
            val = val / 3 + abs(sa - sb) * 200 + g_prv_bid / 2;

            array<int,7> base = f.get_cnt();
            array<int,7> ca = str_cnt(a), cb = str_cnt(b);
            bool six_unused  = !f.rule_used(5);
            bool five_unused = !f.rule_used(4);

            bool straightA = is_any_straight_str(a);
            bool straightB = is_any_straight_str(b);
            char prefer = 'A';
            if (straightA || straightB) {
                int scoreA56 = deck56score_by_cnt_sum(ca[5], ca[6], sa);
                int scoreB56 = deck56score_by_cnt_sum(cb[5], cb[6], sb);
                prefer = (scoreA56 >= scoreB56 ? 'A' : 'B');

                int delta56 = abs(scoreA56 - scoreB56);
                int bump = min(2500, 10 * delta56);
                val += bump;

                bool a_has56 = (ca[5]>0 && ca[6]>0);
                bool b_has56 = (cb[5]>0 && cb[6]>0);
                int min_bid = 0;
                if ((prefer=='A' && a_has56 && !b_has56) || (prefer=='B' && b_has56 && !a_has56)) min_bid = 3000;
                else if ((prefer=='A' && a_has56) || (prefer=='B' && b_has56)) min_bid = 1800;
                else min_bid = 900;
                if (val < min_bid) val = min_bid;
            } else {
                int tot6A = base[6] + ca[6], tot6B = base[6] + cb[6];
                int forcedSixA = (six_unused && tot6A >= 4) ? min(tot6A,5)*6000 : 0;
                int forcedSixB = (six_unused && tot6B >= 4) ? min(tot6B,5)*6000 : 0;
                int tot5A = base[5] + ca[5], tot5B = base[5] + cb[5];
                int forcedFiveA = (five_unused && tot5A >= 5) ? 25000 : 0;
                int forcedFiveB = (five_unused && tot5B >= 5) ? 25000 : 0;

                if (max(forcedSixA, forcedFiveA) > max(forcedSixB, forcedFiveB)) prefer='A';
                else if (max(forcedSixB, forcedFiveB) > max(forcedSixA, forcedFiveA)) prefer='B';
                else {
                    if (sa > sb) prefer='A';
                    else if (sb > sa) prefer='B';
                    else {
                        int wA = 3*ca[6] + 2*ca[5];
                        int wB = 3*cb[6] + 2*cb[5];
                        if (wA > wB) prefer='A';
                        else if (wB > wA) prefer='B';
                        else {
                            int maxA=0,maxB=0;
                            for(int v=1;v<=6;v++){ maxA=max(maxA, base[v]+ca[v]); maxB=max(maxB, base[v]+cb[v]); }
                            if (maxA > maxB) prefer='A';
                            else if (maxB > maxA) prefer='B';
                            else prefer = (sa >= sb ? 'A' : 'B');
                        }
                    }
                }

                int scoreA56 = deck56score_by_cnt_sum(ca[5], ca[6], sa);
                int scoreB56 = deck56score_by_cnt_sum(cb[5], cb[6], sb);
                int delta56 = abs(scoreA56 - scoreB56);
                val += min(1500, 5 * delta56);

                bool pref_has56 = (prefer=='A' ? (ca[5]>0 && ca[6]>0) : (cb[5]>0 && cb[6]>0));
                int min_bid = pref_has56 ? 1500 : 600;
                if (val < min_bid) val = min_bid;
            }

            double opp_zero_rate = (opp_seen_cnt > 0) ? double(opp_zero_cnt) / opp_seen_cnt : 0.0;
            bool opp_always_zero = (opp_zero_rate >= 0.75);
            bool straightPriority = (straightA || straightB);

            auto deck56score = [&](const string& s){
                array<int,7> c{}; for(char ch: s) c[ch-'0']++;
                int sum=0; for(char ch: s) sum += ch-'0';
                return 400*c[6] + 250*c[5] + sum;
            };
            int scoreA56 = deck56score(a), scoreB56 = deck56score(b);
            int delta56  = abs(scoreA56 - scoreB56);

            int bid_min_noncontest = straightPriority ? 900 : 600;
            int bid_min_contest    = straightPriority ? 1500 : 900;
            int bid_extra_56       = (straightPriority ? 6 : 3) * min(100, delta56/100);

            int val_final;
            if (opp_always_zero) {
                bool likely_contest = true;
                val_final = (likely_contest ? bid_min_contest : bid_min_noncontest) + bid_extra_56;
            } else {
                int soft_cap = straightPriority ? 5000 : 3500;
                int base = min(val, soft_cap);
                base = max(base, (prefer=='A' ? bid_min_contest : bid_min_noncontest));
                val_final = base + bid_extra_56;
            }

            if (val_final < 300)   val_final = 300;
            if (val_final > 10000) val_final = 10000;

            f.roll(a, b); g.roll(a, b);
            if (prefer == 'A') {
                cout << "BID A " << val_final << endl; f_prv_type=0; f_prv_bid=val_final;
            } else {
                cout << "BID B " << val_final << endl; f_prv_type=1; f_prv_bid=val_final;
            }
        }
        else if (cmd=="GET") {
            string type,_; int val; in >> type >> _ >> val;
            f.get(type=="A"?0:1); g.get(type=="A"?1:0);
            if (f_prv_type == (_=="A"?0:1)) {
                if (f_prv_type == (type=="A"?0:1)) { f_score_bid -= f_prv_bid; g_score_bid += val; }
                else { f_score_bid += f_prv_bid; g_score_bid -= val; }
            } else { f_score_bid -= f_prv_bid; g_score_bid -= val; }
            g_prv_bid = val;

            opp_seen_cnt++;
            if (val == 0) opp_zero_cnt++;
        }
        else if (cmd=="SCORE") {
            auto [op, s] = f.choose();
            f.put(op, s);
            cout << "PUT " << get_op_name(op) << ' ' << s << endl;
        }
        else if (cmd=="SET") {
            string s_op, s; in >> s_op >> s;
            int op=0; while (get_op_name(op) != s_op) op++;
            g.put(op, s);
        }
        else if (cmd=="FINISH") break;
    }
}
