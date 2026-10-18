// Yacht Auction – aggressive basic-first (#7-like) bidder + dp-based table play

#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
int dp[4096][252][64];
int mn[4096];
int mx[4096];

vector<uint8_t> bits_to_v_bwt_rice(const string& bits) {
	size_t pos = 0;
	auto eof = [&] { return pos >= bits.size(); };
	auto get1 = [&]() -> int {
		if (eof()) throw runtime_error("BitReader EOF");
		return bits[pos++] == '1';
	};
	auto getN_LSB = [&](int n) -> uint32_t {
		uint32_t v = 0;
		for (int i = 0; i < n; ++i) v |= (uint32_t)get1() << i;
		return v;
	};
	auto read_rice_len = [&](int k) -> uint32_t {
		uint32_t q = 0;
		for (;;) { int b = get1(); if (b == 0) break; ++q; }
		uint32_t r = k ? getN_LSB(k) : 0u;
		return (q << k) + r + 1;
	};
	auto ibwt = [&](const vector<uint8_t>& L) -> vector<uint8_t> {
		const int m = (int)L.size();
		if (m == 0) return {};
		uint8_t maxSym = 0;
		for (uint8_t c : L) if (c > maxSym) maxSym = c;
		const int SIG = (int)maxSym + 1;
		vector<int> cnt(SIG, 0);
		for (uint8_t c : L) ++cnt[c];
		vector<int> start(SIG, 0);
		for (int c = 1; c < SIG; ++c) start[c] = start[c - 1] + cnt[c - 1];
		vector<int> occ(SIG, 0), nxt(m);
		for (int i = 0; i < m; ++i) { int c = L[i]; nxt[i] = start[c] + occ[c]++; }
		int pos0 = -1;
		for (int i = 0; i < m; ++i) if (L[i] == 0) { pos0 = i; break; }
		vector<uint8_t> out(m - 1);
		int cur = pos0;
		for (int k = m - 2; k >= 0; --k) cur = nxt[cur], out[k] = L[cur];
		return out;
	};
	vector<uint8_t> out;
	out.reserve(1u << 24);
	vector<uint8_t> L, seq;
	while (true) {
		if ((bits.size() - pos) < 33) break;
		uint32_t count = getN_LSB(24);
		int valBits = (int)getN_LSB(5);
		int k = (int)getN_LSB(4);
		L.clear();
		L.reserve(count);
		size_t produced = 0;
		while (produced < count) {
			uint32_t len = read_rice_len(k);
			uint32_t val = valBits ? getN_LSB(valBits) : 0u;
			if (produced + len > count) len = count - produced;
			L.insert(L.end(), len, (uint8_t)val);
			produced += len;
		}
		seq = ibwt(L);
		for (uint8_t x : seq) out.push_back((uint8_t)(x - 1));
	}
	return out;
}

void init_dp() {
	const int level = 29;
	ifstream in("data.bin", ios::binary);
	int nbit; in.read((char*)&nbit, sizeof nbit);
	string f(nbit, 0);
	for (int i = 0; i < nbit; i += 8) {
		unsigned char val; in.read((char*)&val, sizeof val);
		for (int j = 0; j < 8; j++) {
			if (i + j == nbit) break;
			if (val >> j & 1) f[i + j] = 49;
			else f[i + j] = 48;
		}
	}
	vector<uint8_t> v = bits_to_v_bwt_rice(f);
	int pv = 0;
	for (int i = 0; i < 4095; i++) {
		int val = 0;
		for (int iter = 4; iter >= 0; iter--) val = level * val + v[pv + iter];
		pv += 5;
		mn[i] = val;
	}
	for (int i = 0; i < 4095; i++) {
		int val = 0;
		for (int iter = 4; iter >= 0; iter--) val = level * val + v[pv + iter];
		pv += 5;
        mx[i] = val;
	}
	for (int mask = 0; mask < 4095; mask++) {
		const int range = mx[mask] - mn[mask];
		for (int i = 0; i < 252; i++) {
			for (int j = 0; j < 64; j++) {
				int val = mn[mask] + (v[pv++] * range + level / 2) / level;
				if (val < mn[mask]) val = mn[mask];
				if (val > mx[mask]) val = mx[mask];
				dp[mask][i][j] = val / 1000;
			}
		}
	}
}


// --- 상태 매핑: 5주사위 분포 252개, 10C5 분할 252개 ---
static int seq[252][6];        // pos -> 각 눈(1..6) 개수
static int seq_conv[46656];    // base-6 코드 -> pos (없으면 -1)
static int mask_10C5[252];     // 10개 중 5개 선택 마스크

static inline void init_seq() {
    vector<array<int,6>> all; all.reserve(7776);
    for (int i=0;i<7776;i++){
        array<int,6> cnt{}; int x=i;
        for (int j=0;j<5;j++) { cnt[x%6]++; x/=6; }
        all.push_back(cnt);
    }
    sort(all.begin(), all.end());
    vector<array<int,6>> uniq; uniq.reserve(252);
    for (int i=0;i<(int)all.size();) {
        int j=i+1; while(j<(int)all.size() && all[j]==all[i]) j++;
        uniq.push_back(all[i]); i=j;
    }
    memset(seq_conv, -1, sizeof(seq_conv));
    for (int p=0;p<252;p++){
        int code=0;
        for (int k=0;k<6;k++){ seq[p][k]=uniq[p][k]; code=6*code+uniq[p][k]; }
        seq_conv[code]=p;
    }
    int idx=0;
    for (int m=0;m<(1<<10);m++) if (__builtin_popcount(m)==5) mask_10C5[idx++]=m;
}

static inline string get_op_name(int op){
    static const string name[12] = {
        "ONE","TWO","THREE","FOUR","FIVE","SIX",
        "CHOICE","FOUR_OF_A_KIND","FULL_HOUSE",
        "SMALL_STRAIGHT","LARGE_STRAIGHT","YACHT"
    };
    return name[op];
}

// 내부 스케일(dp와 동일: ×1000 안 붙임)
static inline int calc_score(int op, int x, int pos){
    int a[6]{}, same[7]{}, sum=0, mset=0;
    for (int i=0;i<6;i++){
        a[i]=seq[pos][i];
        if(a[i]){ same[a[i]]++; sum+=(i+1)*a[i]; mset|=(1<<i); }
    }
    if (op==6)  return sum;
    if (op==7)  return (same[4]||same[5]) ? sum : 0;
    if (op==8)  return ((same[2]&&same[3])||same[5]) ? sum : 0;
    if (op==9)  return ((mset&15)==15 || (mset>>1&15)==15 || (mset>>2&15)==15) ? 15 : 0;
    if (op==10) return ((mset&31)==31 || (mset>>1&31)==31) ? 30 : 0;
    if (op==11) return same[5] ? 50 : 0;
    int val=(op+1)*a[op];
    if (x<63 && x+val>=63) val+=35;
    return val;
}

struct Choice { int total, s_now, op, nxt_pos, dx, sel_mask10, cur_pos; };

static inline Choice choose_best_on_10(const vector<int>& v10, int mask, int x){
    int bestTot=INT_MIN, bestS=0, bestOp=-1, bestNxt=-1, bestDx=0, bestSel=0, bestCur=-1;
    int vv[10]; for (int i=0;i<10;i++) vv[i]=v10[i];
    for (int it=0; it<252; ++it){
        int cur[6]{}, nxt[6]{};
        int m = mask_10C5[it];
        for (int i=0;i<10;i++) ((m>>i)&1 ? cur : nxt)[ vv[i]-1 ]++;
        int cur_code=0, nxt_code=0;
        for (int k=0;k<6;k++){ cur_code=6*cur_code+cur[k]; nxt_code=6*nxt_code+nxt[k]; }
        int cur_pos=seq_conv[cur_code], nxt_pos=seq_conv[nxt_code];
        for (int op=0; op<=11; ++op) if (!(mask>>op & 1)){
            int s  = calc_score(op, x, cur_pos);
            int dx = (op<=5) ? (op+1)*cur[op] : 0;
            int nx = x + dx; if (nx>63) nx=63;
            int tot = s + dp[mask|(1<<op)][nxt_pos][nx];
            if (tot > bestTot){
                bestTot = tot; bestS = s; bestOp = op;
                bestNxt = nxt_pos; bestDx = dx; bestSel = m; bestCur = cur_pos;
            }
        }
    }
    return {bestTot,bestS,bestOp,bestNxt,bestDx,bestSel,bestCur};
}

// 5개만 있을 때 최적
static inline pair<int,int> choose_best_on_5(const vector<int>& v5, int mask, int x){
    int cnt[6]{}; for (int v: v5) cnt[v-1]++;
    int code=0; for (int i=0;i<6;i++) code=6*code+cnt[i];
    int pos = seq_conv[code];
    int bestS=-1, bestOp=-1;
    for (int op=0; op<=11; ++op) if (!(mask>>op & 1)){
        int s = calc_score(op, x, pos);
        if (s > bestS){ bestS = s; bestOp = op; }
    }
    return {bestOp, bestS};
}

static inline int vec5_to_pos(const vector<int>& v){
    int cnt[6]{}; for (int x: v) cnt[x-1]++;
    int code=0; for (int i=0;i<6;i++) code=6*code+cnt[i];
    return seq_conv[code];
}
static inline vector<int> pos_to_vec(int pos){
    vector<int> v; v.reserve(5);
    for (int i=0;i<6;i++) for (int c=0;c<seq[pos][i]; ++c) v.push_back(i+1);
    return v;
}

// 실제 점수(×1000) with 상단 보너스
static inline int score_actual_once(int op, const string& d5, int& upper_pts_acc, bool& upper_bonus_given){
    int a[7]{}, b[6]{}, sum=0, mask=0;
    for (char c: d5){ int v=c-'0'; a[v]++; sum+=v; mask|=(1<<(v-1)); }
    for (int i=1;i<=6;i++) b[ a[i] ]++;

    if (op==6) return sum*1000;
    if (op==7) return (b[4]||b[5]) ? sum*1000 : 0;
    if (op==8) return ((b[2]&&b[3])||b[5]) ? sum*1000 : 0;
    if (op==9) return ((mask&15)==15 || (mask>>1&15)==15 || (mask>>2&15)==15) ? 15000 : 0;
    if (op==10) return ((mask&31)==31 || (mask>>1&31)==31) ? 30000 : 0;
    if (op==11) return b[5] ? 50000 : 0;

    int val = a[op+1]*(op+1)*1000;
    if (!upper_bonus_given && upper_pts_acc < 63000 && upper_pts_acc + val >= 63000){
        upper_bonus_given = true;
        val += 35000;
    }
    upper_pts_acc += a[op+1]*(op+1)*1000;
    return val;
}

// 한 쪽(우리/상대)의 “A/B 선택 시 DP가치” 계산
static inline long long dp_value_for_pick(char pick, const vector<int>& carry,
                                          const vector<int>& A, const vector<int>& B,
                                          int mask, int x64){
    if (pick=='A'){
        if (carry.empty()){
            int pA = vec5_to_pos(A);
            return dp[mask][pA][x64];
        }else{
            vector<int> v = carry; v.insert(v.end(), A.begin(), A.end());
            vector<int> vv=v; sort(vv.begin(), vv.end());
            auto C = choose_best_on_10(vv, mask, x64);
            return C.total;
        }
    }else{
        if (carry.empty()){
            int pB = vec5_to_pos(B);
            return dp[mask][pB][x64];
        }else{
            vector<int> v = carry; v.insert(v.end(), B.begin(), B.end());
            vector<int> vv=v; sort(vv.begin(), vv.end());
            auto C = choose_best_on_10(vv, mask, x64);
            return C.total;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_seq();
    init_dp();

    // 우리/상대 상태
    int mask_us=0, x_us=0, mask_op=0, x_op=0;
    vector<int> carry_us, carry_op, lastA, lastB, pend_us, pend_op;
    bool have_pend_us=false, have_pend_op=false;

    long long score_us=0, score_op=0;
    long long bidbal_us=0, bidbal_op=0;
    int upper_us=0, upper_op=0; bool upper_us_bonus=false, upper_op_bonus=false;

    // 컨테스트 추정 강화를 위한 EMA
    bool ema_init=false; double ema_opp=800.0; const double ema_alpha=0.30;

    int prv_want=0;   // 0:A 1:B
    int prv_bid=1;

    string line;
    while (getline(cin, line)){
        if (line.empty()) continue;
        istringstream in(line);
        string cmd; in >> cmd;

        if (cmd=="READY"){
            cout << "OK" << endl;
        }
        else if (cmd=="ROLL"){
            string a,b; in >> a >> b;
            lastA.clear(); lastB.clear();
            for(char c: a) lastA.push_back(c-'0');
            for(char c: b) lastB.push_back(c-'0');
            sort(lastA.begin(), lastA.end());
            sort(lastB.begin(), lastB.end());

            // 우리/상대가 A,B를 잡았을 때 DP 가치
            long long UA = dp_value_for_pick('A', carry_us, lastA, lastB, mask_us, x_us);
            long long UB = dp_value_for_pick('B', carry_us, lastA, lastB, mask_us, x_us);
            long long OA = dp_value_for_pick('A', carry_op, lastA, lastB, mask_op, x_op);
            long long OB = dp_value_for_pick('B', carry_op, lastA, lastB, mask_op, x_op);

            char pick_us = (UA>=UB ? 'A':'B');
            char pick_op = (OA>=OB ? 'A':'B'); // DP 기반 상대 선호 예측
                    
            // 1) 마진(×1000 스케일)과 컨피던스
            long long du = llabs(UA - UB) * 1000;  // our margin in ×1000
            long long dv = llabs(OA - OB) * 1000;  // opp margin in ×1000

            auto sigmoid = [](double z){ return 1.0/(1.0+exp(-z)); };
            double conf_us = sigmoid((du - 12000.0)/4000.0); // >0.5이면 확신 ↑
            double conf_op = sigmoid((dv - 12000.0)/4000.0);

            // 2) 동적 컨테스트 확률
            bool will_contest = (pick_us == pick_op);
            double p_contest = will_contest
                ? max(0.65, 0.75*conf_op + 0.25*conf_us)            // 같은 선택: 최소 0.65로 시작
                : (1.0 - min(0.95, 0.7*conf_op + 0.3*conf_us));     // 다른 선택이어도 뒤집힐 확률 반영

            // 3) 라운드/리드, cap 재정의
            int round_no = __builtin_popcount(mask_us) + 1;
            long long lead = (score_us + bidbal_us) - (score_op + bidbal_op);

            // 컨테스트면 상대 마진도 0.3 섞어 cap 완화
            long long cap = will_contest
                ? (long long) llround(0.95 * (0.7*du + 0.3*dv))
                : (long long) llround(0.95 * du);
            cap = max(0LL, min(cap, 120000LL)); // 상한 살짝 완화(10만→12만)

            // 4) 입찰 계산
            long long bid = 1;

            if (!will_contest) {
                // 비컨테스트 예측: 불확실하면 가드 입찰
                bool uncertain = (conf_op < 0.85) || (conf_us < 0.85); // 임계는 경험적으로 0.85
                if (uncertain) {
                    long long guard = (long long) llround(0.12 * (double)du);
                    if (round_no <= 2) guard = max(guard, 300LL);
                    bid = max(1LL, min(guard, cap));
                } else {
                    bid = 1; // 정말 확신이 높을 때만 1원
                }
            } else {
                // 컨테스트: base와 EMA를 혼합, 초반 완화
                double base = (round_no <= 2 ? 0.38 : 0.46) * (double)du * p_contest;
                double toward_ema = (ema_init ? 0.9 * ema_opp : 0.0);
            
                double lead_mul = 1.0;
                if (lead > 30000)      lead_mul = 0.90;
                else if (lead < -30000) lead_mul = 1.08;
            
                // 과한 극단을 피하기 위해 합성(최댓값 대신 가중 평균)
                double raw = 0.60 * base + 0.40 * min((double)cap, toward_ema);
            
                // 환급 모드: 조건 살짝 보수화(d_us 임계 완화)
                if (lead < -30000 && du < 14000 && p_contest > 0.75 && ema_init && ema_opp > 1500.0) {
                    raw = min((double)cap, max(1.0, ema_opp - 1.0));
                }
            
                bid = (long long) llround(raw * lead_mul);
                bid = max(1LL, min(bid, cap));
            
                // 초반 바닥도 완화
                if (round_no <= 2) bid = max(bid, 300LL);
            
                // 동점 방지 살짝(컨테스트에서는 +1)
                if (p_contest > 0.5) ++bid;
            }

            cout << "BID " << pick_us << " " << bid << endl;
            prv_want = (pick_us=='A'?0:1);
            prv_bid  = (int)bid;

        }
        else if (cmd=="GET"){
            // GET g g0 x0
            string g, g0; int x0; in >> g >> g0 >> x0;
            bool gotA = (g=="A");
            bool oppWantedA = (g0=="A");

            // 우리/상대가 실제로 받은 5개
            vector<int> got_us = (gotA ? lastA : lastB);
            vector<int> got_op = (gotA ? lastB : lastA);

            // carry/pend 업데이트
            if (carry_us.empty()){ carry_us = std::move(got_us); have_pend_us=false; pend_us.clear(); }
            else { pend_us = std::move(got_us); have_pend_us=true; }

            if (carry_op.empty()){ carry_op = std::move(got_op); have_pend_op=false; pend_op.clear(); }
            else { pend_op = std::move(got_op); have_pend_op=true; }

            // 입찰 손익
            bool we_wantedA = (prv_want==0);
            bool we_got_wanted = (we_wantedA ? gotA : !gotA);
            bidbal_us += (we_got_wanted ? -prv_bid : +prv_bid);

            bool opp_gotA = !gotA;
            bool opp_got_wanted = (oppWantedA ? opp_gotA : !opp_gotA);
            bidbal_op += (opp_got_wanted ? -x0 : +x0);

            // 컨테스트였으면 EMA 갱신
            bool contested = ( (we_wantedA && oppWantedA) || (!we_wantedA && !oppWantedA) );
            if (contested){
                if (!ema_init){ ema_opp = x0; ema_init=true; }
                else ema_opp = ema_alpha * x0 + (1.0-ema_alpha) * ema_opp;
            }
        }
        else if (cmd=="SCORE"){
            if (have_pend_us){
                vector<int> v10 = carry_us; v10.insert(v10.end(), pend_us.begin(), pend_us.end());
                sort(v10.begin(), v10.end());
                auto C = choose_best_on_10(v10, mask_us, x_us);

                string d5; d5.reserve(5);
                for (int i=0;i<10;i++) if ((C.sel_mask10>>i)&1) d5.push_back(char('0'+v10[i]));

                // 상태 갱신
                mask_us |= (1<<C.op);
                x_us += C.dx; if (x_us>63) x_us=63;
                carry_us = pos_to_vec(C.nxt_pos);
                pend_us.clear(); have_pend_us=false;

                score_us += score_actual_once(C.op, d5, upper_us, upper_us_bonus);

                cout << "PUT " << get_op_name(C.op) << ' ' << d5 << endl;
            }else{
                if (carry_us.empty()){ cout << "PUT ONE 11111" << endl; continue; }
                auto [op, _s] = choose_best_on_5(carry_us, mask_us, x_us);
                string d5; d5.reserve(5);
                for (int v: carry_us) d5.push_back(char('0'+v));
                mask_us |= (1<<op);
                score_us += score_actual_once(op, d5, upper_us, upper_us_bonus);
                cout << "PUT " << get_op_name(op) << ' ' << d5 << endl;
            }
        }
        else if (cmd=="SET"){
            // 상대 득점 반영 + carry_op 갱신 + x_op 업데이트
            string name_op, d5; in >> name_op >> d5;
            int op=0; while(get_op_name(op)!=name_op) ++op;

            // 상단 누적 추적용 dx
            if (op<=5){
                int cnt=0; for(char c: d5) if (c-'0'==op+1) cnt++;
                x_op += (op+1)*cnt; if (x_op>63) x_op=63;
            }

            score_op += score_actual_once(op, d5, upper_op, upper_op_bonus);
            mask_op |= (1<<op);

            vector<int> v10 = carry_op;
            if (have_pend_op){ v10.insert(v10.end(), pend_op.begin(), pend_op.end()); have_pend_op=false; pend_op.clear(); }
            sort(v10.begin(), v10.end());
            int need[7]{}; for(char c: d5) need[c-'0']++;
            vector<int> nxt;
            for (int v: v10){
                if (need[v]>0) need[v]--;
                else nxt.push_back(v);
            }
            carry_op = std::move(nxt);
        }
        else if (cmd=="FINISH"){
            break;
        }
    }
    return 0;
}