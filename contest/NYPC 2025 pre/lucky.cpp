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

// 스트레이트 감지
static bool is_small_straight_str(const string& s) {
    int mask = 0; for (char ch : s) mask |= 1 << (ch - '1');
    return ((mask & 15) == 15) || (((mask >> 1) & 15) == 15) || (((mask >> 2) & 15) == 15);
}
static bool is_large_straight_str(const string& s) {
    int mask = 0; for (char ch : s) mask |= 1 << (ch - '1');
    return ((mask & 31) == 31) || (((mask >> 1) & 31) == 31);
}
static bool is_any_straight_str(const string& s) { return is_small_straight_str(s) || is_large_straight_str(s); }

// 5/6 우선 점수
static int deck56score_by_cnt_sum(int c5, int c6, int sum) {
    return 400 * c6 + 250 * c5 + sum; // 6>5>합계
}

struct board {
    board() : used_mask(0), cnt{}, score_up(0), score_down() {}
    void roll(string a, string b) { prv_a = a; prv_b = b; }
    void get(int type) { if (type == 0) update(prv_a, 1); else update(prv_b, 1); }
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
                if (acc.size() != 5) return;
                for (int op = 0; op <= 11; op++) {
                    if (used_mask >> op & 1) continue;
                    int val = calc(op, acc);
                    if (op == 4) { int c5=0; for(char ch:acc) if(ch=='5') c5++; if (c5 <= 2) val -= 10000; }
                    if (op == 5) { int c6=0; for(char ch:acc) if(ch=='6') c6++; if (c6 <= 2) val -= 10000; }
                    if (ret_val >= val) continue;
                    ret_op = op; ret_s = acc; ret_val = val;
                }
                return;
            }
            for (int i=0;i<=cnt[dep];i++) { self(self, dep+1, acc); acc.push_back(dep+'0'); if (acc.size()>5) break; }
        };
        rec(rec, 1, string{});
        return pair(ret_op, ret_s);
    }

    auto choose() {
        // 빠른 YACHT
        if (~used_mask >> 11 & 1 && cnt[1] == 5) return pair(11, string("11111"));
        if (~used_mask >> 11 & 1 && cnt[2] == 5) return pair(11, string("22222"));
        if (~used_mask >> 11 & 1 && cnt[3] == 5) return pair(11, string("33333"));

        // SIX/FIVE 강제
        if (~used_mask >> 5 & 1 && cnt[6] >= 5) return pair(5, string("66666"));
        if (~used_mask >> 5 & 1 && cnt[6] == 4) {
            int p=1; while (cnt[p]==0) p++;
            return pair(5, string("6666") + char(p+'0'));
        }
        if (~used_mask >> 4 & 1 && cnt[5] == 5) return pair(4, string("55555"));

        int ret_op=-1; string ret_s; int ret_val = -1000000000;
        auto rec = [&](const auto& self, int dep, string acc)->void{
            if (dep==7) {
                if (acc.size()!=5) return;
                for (int op=0; op<=11; op++) {
                    if (used_mask>>op & 1) continue;
                    int round = __builtin_popcount((unsigned)used_mask);
                    int val = calc(op, acc);

                    if (op==6 && round<=3) val -= 10000; // CHOICE 초반 억제
                    if (round<=3 && op==9 && val!=0) val += 10000;
                    if (round<=3 && op==10&& val!=0) val += 10000;

                    if (op==4 && cnt[5]<4) val -= 10000;
                    if (op==5 && cnt[6]<4) val -= 10000;

                    // 63k 경로 보정(비상단 벌점)
                    if (op>5) {
                        int three_budget=0;
                        for (int i=0;i<6;i++) if (((used_mask>>i)&1)==0) three_budget += 3*(i+1)*1000;
                        bool jeopardy = (score_up + three_budget < 63000);
                        if (jeopardy) {
                            int c5=0,c6=0; for(char ch:acc){ if(ch=='5') c5++; else if(ch=='6') c6++; }
                            if (((used_mask>>4)&1)==0) val -= 2500*c5;
                            if (((used_mask>>5)&1)==0) val -= 3000*c6;
                        }
                    }

                    // 소형 MC
                    {
                        update(acc, -1); used_mask ^= 1<<op;
                        int sum=0;
                        for (int iter=0; iter<3; iter++) {
                            string t; for (int i=0;i<5;i++) t.push_back(gen_rand(1,6)+'0');
                            update(t, 1);
                            auto [nop, ns] = choose_greedy();
                            sum += calc(nop, ns);
                            update(t, -1);
                        }
                        val += sum/3;
                        update(acc, 1); used_mask ^= 1<<op;
                    }

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

    int get_score() { return score_up + score_down; }

private:
    int used_mask;
    int cnt[7];
    int score_up;
    int score_down;
    string prv_a, prv_b;

    void update(string s, int x) { for (int i=0;i<5;i++) cnt[s[i]-'0'] += x; }

    int calc(int op, string s) {
        int a[7]{}, b[6]{}; int sum=0, mask=0;
        for (int i=0;i<5;i++) a[s[i]-'0']++;
        for (int i=1;i<=6;i++) b[a[i]]++;
        for (int i=0;i<5;i++) sum += s[i]-'0';
        for (int i=0;i<5;i++) mask |= 1 << (s[i]-'1');
        if (op==6)  return sum*1000;
        if (op==7)  return (b[4]||b[5]) ? sum*1000 : 0;
        if (op==8)  return ((b[2]&&b[3])||b[5]) ? sum*1000 : 0;
        if (op==9)  return (((mask&15)==15)||(((mask>>1)&15)==15)||(((mask>>2)&15)==15)) ? 15000 : 0;
        if (op==10) return (((mask&31)==31)||(((mask>>1)&31)==31)) ? 30000 : 0;
        if (op==11) return b[5] ? 50000 : 0;
        int val = a[op+1]*(op+1)*1000;
        if (score_up<63000 && score_up+val>=63000) val += 35000;
        return val;
    }
};

static array<int,7> str_cnt(const string& s) { array<int,7> c{}; for (char ch: s) c[ch-'0']++; return c; }

// main() 위쪽 전역 또는 main 안의 상태와 함께 둘 수 있음
int opp_zero_cnt = 0;   // 상대가 0 입찰한 횟수
int opp_seen_cnt = 0;   // 상대 입찰 관측 횟수

int main() {
    board f, g;
    int f_score_bid=0, g_score_bid=0;
    int f_prv_type=0, f_prv_bid=0, g_prv_bid=0;

    while (1) {
        string input; if(!getline(cin, input)) break;
        if (input.empty()) continue;
        istringstream in(input);
        string cmd; in >> cmd;

        if (cmd=="READY") {
            cout << "OK" << endl;
        }
        else if (cmd=="ROLL") {
            string a,b; in >> a >> b;

            // 합
            int sa=0,sb=0; for(int i=0;i<5;i++) sa+=a[i]-'0'; for(int i=0;i<5;i++) sb+=b[i]-'0';

            // 기본 입찰가(너무 커지는 걸 막기 위해 이후 캡 적용)
            int f_score = f_score_bid + f.get_score();
            int g_score = g_score_bid + g.get_score();
            int val = (f_score - g_score) / 10;
            if (val < 0) val = 0;
            if (val > 100000) val = 100000;
            val = val / 3 + abs(sa - sb) * 200 + g_prv_bid / 2;

            // 덱 선택 로직
            array<int,7> base = f.get_cnt();
            array<int,7> ca = str_cnt(a), cb = str_cnt(b);
            bool six_unused  = !f.rule_used(5);
            bool five_unused = !f.rule_used(4);

            // 1) 스트레이트 우선: 보이면 5/6 많은 쪽 1순위
            bool straightA = is_any_straight_str(a);
            bool straightB = is_any_straight_str(b);
            char prefer = 'A';
            if (straightA || straightB) {
                int scoreA56 = deck56score_by_cnt_sum(ca[5], ca[6], sa);
                int scoreB56 = deck56score_by_cnt_sum(cb[5], cb[6], sb);
                prefer = (scoreA56 >= scoreB56 ? 'A' : 'B');

                // 과도한 가중치 대신 소폭 보정 + 최소입찰선
                int delta56 = abs(scoreA56 - scoreB56);
                int bump = min(2500, 10 * delta56); // 과하지 않게
                val += bump;

                bool a_has56 = (ca[5]>0 && ca[6]>0);
                bool b_has56 = (cb[5]>0 && cb[6]>0);
                int min_bid = 0;
                if ((prefer=='A' && a_has56 && !b_has56) || (prefer=='B' && b_has56 && !a_has56)) min_bid = 3000;
                else if ((prefer=='A' && a_has56) || (prefer=='B' && b_has56)) min_bid = 1800;
                else min_bid = 900;
                if (val < min_bid) val = min_bid;
            } else {
                // 2) 강제 SIX/FIVE 가능 여부
                int tot6A = base[6] + ca[6], tot6B = base[6] + cb[6];
                int forcedSixA = (six_unused && tot6A >= 4) ? min(tot6A,5)*6000 : 0;
                int forcedSixB = (six_unused && tot6B >= 4) ? min(tot6B,5)*6000 : 0;
                int tot5A = base[5] + ca[5], tot5B = base[5] + cb[5];
                int forcedFiveA = (five_unused && tot5A >= 5) ? 25000 : 0;
                int forcedFiveB = (five_unused && tot5B >= 5) ? 25000 : 0;

                if (max(forcedSixA, forcedFiveA) > max(forcedSixB, forcedFiveB)) prefer='A';
                else if (max(forcedSixB, forcedFiveB) > max(forcedSixA, forcedFiveA)) prefer='B';
                else {
                    // 3) 합 비교 → 4) 6/5 가중치 → 5) 같은 눈 최대 잠재력
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

                // 5/6 차이는 가볍게만 반영
                int scoreA56 = deck56score_by_cnt_sum(ca[5], ca[6], sa);
                int scoreB56 = deck56score_by_cnt_sum(cb[5], cb[6], sb);
                int delta56 = abs(scoreA56 - scoreB56);
                val += min(1500, 5 * delta56);

                // 최소입찰선(0 금지)
                bool pref_has56 = (prefer=='A' ? (ca[5]>0 && ca[6]>0) : (cb[5]>0 && cb[6]>0));
                int min_bid = pref_has56 ? 1500 : 600;
                if (val < min_bid) val = min_bid;
            }

            // --- 상대 패턴(0입찰 성향) + 56 가중 반영한 최종 입찰 금액 산출 ---
						// 상대 0입찰 패턴 추정
						double opp_zero_rate = (opp_seen_cnt > 0) ? double(opp_zero_cnt) / opp_seen_cnt : 0.0;
						bool opp_always_zero = (opp_zero_rate >= 0.75); // 최근 대부분 0이면 '0 모드'
						
						// 스트레이트/56 지표
						bool straightPriority = (straightA || straightB);
						
						auto deck56score = [&](const string& s){
						    array<int,7> c{}; for(char ch: s) c[ch-'0']++;
						    int sum=0; for(char ch: s) sum += ch-'0';
						    return 400*c[6] + 250*c[5] + sum;  // 6>5>합
						};
						int scoreA56 = deck56score(a), scoreB56 = deck56score(b);
						int delta56  = abs(scoreA56 - scoreB56);
						
						// 기본 최저선(컨테스트/비컨테스트), 56 가중 소폭
						int bid_min_noncontest = straightPriority ? 900 : 600;   // 상대가 다른 묶음이면 이 정도면 충분
						int bid_min_contest    = straightPriority ? 1500 : 900;  // 같은 묶음 노릴 때
						int bid_extra_56       = (straightPriority ? 6 : 3) * min(100, delta56/100); // 과하지 않게
						
						int val_final;
						if (opp_always_zero) {
						    // 상대가 계속 0이면 초소형만(과소비 금지)
						    bool likely_contest = true; // 0이어도 같은 묶음 고를 수 있으니 살짝만 위
						    val_final = (likely_contest ? bid_min_contest : bid_min_noncontest) + bid_extra_56;
						} else {
						    // 기존 산출 val을 쓰되 소프트 캡으로 과투입 방지
						    int soft_cap = straightPriority ? 5000 : 3500;
						    int base = val;
						    base = min(base, soft_cap);
						    base = max(base, (prefer=='A' ? bid_min_contest : bid_min_noncontest));
						    val_final = base + bid_extra_56;
			}

// 절대 상한/하한(요구사항 반영)
if (val_final < 300)   val_final = 300;    // 0 금지(최소 아주 작게)
if (val_final > 10000) val_final = 10000;  // 1만 초과 금지

// 출력
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
            // 기존 GET 처리 마지막에 이미 g_prv_bid = val; 이 있음
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
