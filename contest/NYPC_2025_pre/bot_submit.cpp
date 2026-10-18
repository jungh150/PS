// bot_submit.cpp — jh.cpp과 동일한 게임 로직/프로토콜, BID만 학습 에이전트 사용
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

// ====== jh.cpp의 보드(그대로) ======
struct board {
    board() :
        used_mask(0),
        cnt{},
        score_up(0),
        score_down() {}
    void roll(string a, string b) {
        prv_a = a;
        prv_b = b;
    }
    void get(int type) {
        if (type == 0) update(prv_a, 1);
        else update(prv_b, 1);
    }
    void put(int op, string s) {
        used_mask |= 1 << op;
        update(s, -1);
        if (op <= 5) score_up += calc(op, s);
        else score_down += calc(op, s);
    }
    auto choose_greedy() {
        int ret_op = -1;
        string ret_s;
        int ret_val = -1;
        auto rec = [&](const auto& self, int dep, string acc) -> void {
            if (dep == 7) {
                if (acc.size() != 5) return;
                for (int op = 0; op <= 11; op++) {
                    if (used_mask >> op & 1) continue;
                    int val = calc(op, acc);
                    if (ret_val >= val) continue;
                    ret_op = op;
                    ret_s = acc;
                    ret_val = val;
                }
                return;
            }
            for (int i = 0; i <= cnt[dep]; i++) {
                self(self, dep + 1, acc);
                acc.push_back(dep + '0');
                if (acc.size() > 5) break;
            }
        };
        rec(rec, 1, string{});
        return pair(ret_op, ret_s);
    }
    auto choose() {
        if (~used_mask >> 11 & 1 && cnt[1] == 5) return pair(11, string("11111"));
        if (~used_mask >> 11 & 1 && cnt[2] == 5) return pair(11, string("22222"));
        if (~used_mask >> 11 & 1 && cnt[3] == 5) return pair(11, string("33333"));
        if (~used_mask >> 5 & 1 && cnt[6] == 5) return pair(5, string("66666"));
        if (~used_mask >> 4 & 1 && cnt[5] == 5) return pair(4, string("55555"));
        if (~used_mask >> 5 & 1 && cnt[6] == 4) {
            int p = 1;
            while (cnt[p] == 0) p++;
            return pair(5, string("6666") + char(p + '0'));
        }
        if (~used_mask >> 4 & 1 && cnt[5] == 4) {
            int p = 1;
            while (p == 5 || cnt[p] == 0) p++;
            return pair(4, string("5555") + char(p + '0'));
        }
        int ret_op = -1;
        string ret_s;
        int ret_val = -1e9;
        auto rec = [&](const auto& self, int dep, string acc) -> void {
            if (dep == 7) {
                if (acc.size() != 5) return;
                for (int op = 0; op <= 11; op++) {
                    if (used_mask >> op & 1) continue;
                    int round = __builtin_popcount(used_mask);
                    int val = calc(op, acc);
                    if (round != 11 && op == 6) val -= 5000;
                    if (round <= 3 && op == 9 && val != 0) val += 10000;
                    if (round <= 3 && op == 10 && val != 0) val += 10000;
                    if (op == 4 && cnt[5] < 4) val -= 10000;
                    if (op == 5 && cnt[6] < 4) val -= 10000;
                    if (op == 9 && acc.back() <= '5') val += 6000;
                    if (op == 10 && acc.back() <= '5') val += 6000;
                    if (op == 11 && acc.back() >= '5') val -= 10000;
                    {
                        update(acc, -1);
                        used_mask ^= 1 << op;
                        string nxt;
                        for (int i = 1; i <= 6; i++) nxt += string(cnt[i], 1 + '0');
                        int sum = 0;
                        for (int iter = 0; iter < 3; iter++) {
                            string t;
                            for (int i = 0; i < 5; i++) t.push_back(gen_rand(1, 6) + '0');
                            update(t, 1);
                            auto [nop, ns] = choose_greedy();
                            sum += calc(nop, ns);
                            update(t, -1);
                        }
                        val += sum / 3;
                        update(acc, 1);
                        used_mask ^= 1 << op;
                    }
                    if (ret_val >= val) continue;
                    ret_op = op;
                    ret_s = acc;
                    ret_val = val;
                }
                return;
            }
            for (int i = 0; i <= cnt[dep]; i++) {
                self(self, dep + 1, acc);
                acc.push_back(dep + '0');
                if (acc.size() > 5) break;
            }
        };
        rec(rec, 1, string{});
        return pair(ret_op, ret_s);
    }
    int get_score() {
        return score_up + score_down;
    }
private:
    int used_mask;
    int cnt[7];
    int score_up;
    int score_down;
    string prv_a;
    string prv_b;
    void update(string s, int x) {
        for (int i = 0; i < 5; i++) cnt[s[i] - '0'] += x;
    }
    int calc(int op, string s) {
        int a[7]{}, b[6]{};
        int sum = 0, mask = 0;
        for (int i = 0; i < 5; i++) a[s[i] - '0']++;
        for (int i = 1; i <= 6; i++) b[a[i]]++;
        for (int i = 0; i < 5; i++) sum += s[i] - '0';
        for (int i = 0; i < 5; i++) mask |= 1 << (s[i] - '1');
        if (op == 6) return sum * 1000;
        if (op == 7) return b[4] || b[5] ? sum * 1000 : 0;
        if (op == 8) return b[2] && b[3] || b[5] ? sum * 1000 : 0;
        if (op == 9) return ((mask & 15) == 15) || ((mask >> 1 & 15) == 15) || ((mask >> 2 & 15) == 15) ? 15000 : 0;
        if (op == 10) return ((mask & 31) == 31) || ((mask >> 1 & 31) == 31) ? 30000 : 0;
        if (op == 11) return b[5] ? 50000 : 0;
        int val = a[op + 1] * (op + 1) * 1000;
        if (score_up < 63000 && score_up + val >= 63000) val += 35000;
        return val;
    }
};

// ====== (추가) 학습용 상태 인코딩 & MLP ======
static const vector<int> BID_BUCKET_VALUES = {
    0, 300, 600, 900, 1200, 1500, 1800, 2100, 2400, 2700, 3000,
    3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000,
    12000, 14000, 16000, 18000, 20000
};

// 섀도 보드: 학습 상태(feature) 계산용 (게임 로직에는 영향 X)
struct Shadow {
    bool used[12]{};         // 각 규칙 사용여부
    int upper_sum_faces = 0; // 상단 칸의 얼굴값 합(최대 63)
};

static inline int rule_index_from_name(const string& s){
    for(int i=0;i<12;i++) if (get_op_name(i)==s) return i;
    return 0;
}

// === 학습과 동일한 인코딩: [ round/13, upper/63, used[12], A[5]/6, B[5]/6 ] ===
static inline vector<float> encode_state(const Shadow& my, const Shadow& /*opp*/,
                                         const string& A, const string& B, int round1to12){
    vector<float> st; st.reserve(24);
    st.push_back( max(1,min(12, round1to12)) / 13.0f );
    st.push_back( min(63, my.upper_sum_faces) / 63.0f );
    for(int i=0;i<12;i++) st.push_back(my.used[i]?1.0f:0.0f);
    for(int i=0;i<5;i++) st.push_back( (A[i]-'0') / 6.0f );
    for(int i=0;i<5;i++) st.push_back( (B[i]-'0') / 6.0f );
    return st;
}
static inline int dice_sum_faces(const string& s){ int t=0; for(char c: s) t+=(c-'0'); return t; }

struct MLP {
    int in_dim=24, hidden=64, bundle_out=2, bid_out=(int)BID_BUCKET_VALUES.size();
    vector<float> W1,b1,W2,b2,Wb,bb,Wd,bd;

    bool load(const string& path){
        FILE* fp=fopen(path.c_str(),"rb"); if(!fp) return false;
        auto rd=[&](vector<float>& v, size_t n){ v.resize(n); return fread(v.data(),sizeof(float),n,fp)==n; };
        if(!rd(W1, in_dim*hidden)) return false;
        if(!rd(b1, hidden)) return false;
        if(!rd(W2, hidden*hidden)) return false;
        if(!rd(b2, hidden)) return false;
        if(!rd(Wb, hidden*bundle_out)) return false;
        if(!rd(bb, bundle_out)) return false;
        if(!rd(Wd, hidden*bid_out)) return false;
        if(!rd(bd, bid_out)) return false;
        fclose(fp); return true;
    }
    static vector<float> fc(const vector<float>& x,const vector<float>& W,const vector<float>& b,
                            int in_size,int out_size,bool relu){
        vector<float> y(out_size,0.f);
        for(int o=0;o<out_size;o++){
            float s=b[o];
            const float* w=&W[o*in_size];
            for(int i=0;i<in_size;i++) s += x[i]*w[i];
            y[o]= relu? (s>0?s:0.f): s;
        }
        return y;
    }
    pair<int,int> predict(const vector<float>& st) const {
        auto h1 = fc(st, W1, b1, in_dim, hidden, true);
        auto h2 = fc(h1, W2, b2, hidden, hidden, true);
        auto ob = fc(h2, Wb, bb, hidden, bundle_out, false);
        auto od = fc(h2, Wd, bd, hidden, bid_out, false);
        int bundle_choice = int(max_element(ob.begin(), ob.end()) - ob.begin()); // 0:A, 1:B
        int bid_bucket    = int(max_element(od.begin(), od.end()) - od.begin());
        return {bundle_choice, bid_bucket};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // jh.cpp와 같은 보드(실제 게임 상태)
    board f;
    board g;

    // 학습 상태 추적을 위한 섀도 보드(인코딩 전용)
    Shadow fS, gS;

    // 학습 모델
    MLP model;
    bool has_model = model.load("data.bin"); // 없으면 jh 휴리스틱으로 BID

    int f_score_bid = 0;
    int g_score_bid = 0;
    int f_prv_type = 0;
    int f_prv_bid = 0;
    int g_prv_bid = 0;

    // === 핵심 변경: 학습과 동일하게 라운드 1..12를 명시적으로 사용 ===
    int round_counter = 0; // ROLL 때 1씩 증가 (최대 12)

    while (1) {
        string input; if (!getline(cin, input)) break;
        istringstream in(input);
        string cmd; in >> cmd;

        if (cmd == "READY") {
            cout << "OK" << endl;
        }
        else if (cmd == "ROLL") {
            string a, b; in >> a >> b;

            // 실제 라운드 증가 (학습 환경과 동일하게 1..12)
            if (round_counter < 12) round_counter++;

            // jh 흐름 유지 (휴리스틱 값 계산)
            int sa = dice_sum_faces(a);
            int sb = dice_sum_faces(b);
            int f_score = f_score_bid + f.get_score();
            int g_score = g_score_bid + g.get_score();
            int val = (f_score - g_score) / 10;
            if (val < 0) val = 0;
            if (val > 100000) val = 100000;
            val = val / 3 + abs(sa - sb) * 200 + g_prv_bid / 2;

            // 보드에 ROLL 반영(원본과 동일)
            f.roll(a, b);
            g.roll(a, b);

            // ====== 여기만 학습 에이전트로 변경 ======
            int bundle_choice = (sa >= sb ? 0 : 1); // 기본값(폴백)
            int bid_value = val;                    // 기본값(폴백)

            if (has_model) {
                // 학습과 동일 인코딩: (라운드=1..12 고정, upper_sum_faces/63, used flags, A/B)
                auto state = encode_state(fS, gS, a, b, round_counter);
                auto [bc, bbk] = model.predict(state);
                bundle_choice = bc;                            // 0:A, 1:B
                bid_value     = BID_BUCKET_VALUES[bbk];
            } else {
                cout << "error";
            }

            if (bundle_choice == 0) {
                cout << "BID A " << bid_value << endl;
                f_prv_type = 0;
                f_prv_bid = bid_value;
            } else {
                cout << "BID B " << bid_value << endl;
                f_prv_type = 1;
                f_prv_bid = bid_value;
            }
        }
        else if (cmd == "GET") {
            string type; in >> type;
            string _; in >> _;
            int val; in >> val;
            // 원본 jh 로직 그대로
            f.get(type == "A" ? 0 : 1);
            g.get(type == "A" ? 1 : 0);
            if (f_prv_type == (_ == "A" ? 0 : 1)) {
                if (f_prv_type == (type == "A" ? 0 : 1)) {
                    f_score_bid -= f_prv_bid;
                    g_score_bid += val;
                }
                else {
                    f_score_bid += f_prv_bid;
                    g_score_bid -= val;
                }
            }
            else {
                f_score_bid -= f_prv_bid;
                g_score_bid -= val;
            }
            g_prv_bid = val;

            // 섀도 큐잉은 하지 않아도 됨. SCORE/SET 때 실제 사용 주사위가 오므로 그때만 갱신.
        }
        else if (cmd == "SCORE") {
            auto [op, s] = f.choose();
            f.put(op, s);
            cout << "PUT " << get_op_name(op) << ' ' << s << endl;

            // 섀도 보드 갱신(내가 사용한 규칙/upper 합) — 학습 인코딩용
            if (0 <= op && op <= 11) fS.used[op] = true;
            if (0 <= op && op <= 5) {
                int face = op + 1;
                int cnt = 0; for (char c: s) if (c-'0'==face) cnt++;
                fS.upper_sum_faces += face * cnt;
                if (fS.upper_sum_faces > 63) fS.upper_sum_faces = 63;
            }
        }
        else if (cmd == "SET") {
            string s_op; in >> s_op;
            string s; in >> s;
            int op = rule_index_from_name(s_op);
            g.put(op, s);

            // 섀도 보드(상대)도 동일하게 갱신 — 학습 인코딩용
            if (0 <= op && op <= 11) gS.used[op] = true;
            if (0 <= op && op <= 5) {
                int face = op + 1;
                int cnt = 0; for (char c: s) if (c-'0'==face) cnt++;
                gS.upper_sum_faces += face * cnt;
                if (gS.upper_sum_faces > 63) gS.upper_sum_faces = 63;
            }
        }
        else if (cmd == "FINISH") {
            break;
        }
    }
}
