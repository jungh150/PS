#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u32 = unsigned int;

int dp[4096][252][64];
int seq[252][6];
int seq_conv[46656];
int mask_10C5[252];

void init_dp(const int lim = 29) {
	auto conv_bits = [](const string& s) {
		int pos = 0;
		auto f = [&](int n) {
			int x = 0;
			for (int i = 0; i < n; i++) if (s[pos++] & 1) x |= 1 << i;
			return x;
		};
		auto g = [&](int k) {
			int q = 0;
			while (s[pos++] & 1) q++;
			return (q << k) + f(k) + 1;
		};
		auto ibwt = [&](const string& s) {
			if (s.empty()) return string{};
			int mx = 0;
			for (int x : s) mx = max(mx, x);
			const int n = s.size();
			const int sz = mx + 1;
			vector cnt(sz, 0), occ(sz, 0), nxt(n, 0);
			vector p(sz, 0);
			for (char c : s) cnt[c]++;
			for (int i = 1; i < sz; i++) p[i] = p[i - 1] + cnt[i - 1];
			for (int i = 0; i < n; i++) nxt[i] = p[s[i]] + occ[s[i]]++;
			string ret(n - 1, 0);
			int pos = s.find('\0');
			for (int k = n - 2; k >= 0; --k) pos = nxt[pos], ret[k] = s[pos];
			return ret;
		};
		string ret;
		while (s.size() - pos >= 32) {
			string t;
			int cnt = f(24), a = f(5), b = f(4);
			for (int i = 0; i < cnt;) {
				int len = min(g(b), cnt - i);
				int val = f(a);
				t.insert(t.end(), len, val);
				i += len;
			}
			for (char x : ibwt(t)) ret.push_back(x - 1);
		}
		return ret;
	};
	ifstream in("data.bin", ios::binary);
	int nbit; in.read((char*)&nbit, sizeof nbit);
	string s(nbit, 48);
	for (int i = 0; i < nbit; i += 8) {
		unsigned char c; in.read((char*)&c, sizeof c);
		for (int j = 0; j < 8 && i + j < nbit; j++) s[i + j] |= c >> j & 1;
	}
	string t = conv_bits(s);
	int pos = 0, v[2][4095]{};
	for (int iter = 0; iter < 2; iter++) {
		for (int i = 0; i < 4095; i++) {
			int& val = v[iter][i];
			for (int j = 4; j >= 0; j--) val = lim * val + t[pos + j];
			pos += 5;
		}
	}
	for (int mask = 0; mask < 4095; mask++) {
		const int len = v[1][mask] - v[0][mask];
		for (int i = 0; i < 252; i++) {
			for (int j = 0; j < 64; j++) {
				int val = min((t[pos++] * len + lim / 2) / lim, len);
				dp[mask][i][j] = v[0][mask] + val;
			}
		}
	}
}

void init_seq() {
	int ord = 0, v[6]{};
	auto rec = [&](const auto& self, int dep) -> void {
		if (dep == 6) {
			int acc = 0, val = 0;
			for (int i = 0; i < 6; i++) acc += v[i];
			for (int i = 0; i < 6; i++) val = 6 * val + v[i];
			if (acc != 5) return;
			for (int i = 0; i < 6; i++) seq[ord][i] = v[i];
			seq_conv[val] = ord++;
			return;
		}
		for (int i = 0; i <= 5; i++) {
			v[dep] = i;
			self(self, dep + 1);
		}
	};
	rec(rec, 0);
	for (int i = 0, p = 0; i < 1 << 10; i++) {
		if (__builtin_popcount(i) != 5) continue;
		mask_10C5[p++] = i;
	}
}

string get_op_name(int op) {
	static string v[]{
		"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX",
		"CHOICE", "FOUR_OF_A_KIND", "FULL_HOUSE",
		"SMALL_STRAIGHT", "LARGE_STRAIGHT", "YACHT"
	};
	return v[op];
}

int calc_score(int op, int x, int pos) {
	int a[6]{}, b[7]{}, sum = 0, mask = 0;
	for (int i = 0; i < 6; i++) {
		a[i] = seq[pos][i];
		if (a[i] == 0) continue;
		b[a[i]]++;
		sum += (i + 1) * a[i];
		mask |= (1 << i);
	}
	if (op == 6) return sum * 1000;
	if (op == 7) return (b[4] || b[5]) ? (sum * 1000) : 0;
	if (op == 8) return ((b[2] && b[3]) || b[5]) ? (sum * 1000) : 0;
	if (op == 9) return ((mask & 15) == 15 || (mask >> 1 & 15) == 15 || (mask >> 2 & 15) == 15) ? 15000 : 0;
	if (op == 10) return ((mask & 31) == 31 || (mask >> 1 & 31) == 31) ? 30000 : 0;
	if (op == 11) return b[5] ? 50000 : 0;
	int val = (op + 1) * a[op];
	if (x < 63 && x + val >= 63) val += 35;
	return val * 1000;
}

int score_actual_once(int op, const string& d5, int& upper_pts_acc, bool& upper_bonus_given) {
	int a[7]{}, b[6]{}, sum = 0, mask = 0;
	for (char c : d5) {
		int v = c - '0';
		a[v]++;
		sum += v;
		mask |= (1 << (v - 1));
	}
	for (int i = 1; i <= 6; i++) b[a[i]]++;
	if (op == 6) return sum * 1000;
	if (op == 7) return (b[4] || b[5]) ? sum * 1000 : 0;
	if (op == 8) return ((b[2] && b[3]) || b[5]) ? sum * 1000 : 0;
	if (op == 9) return ((mask & 15) == 15 || (mask >> 1 & 15) == 15 || (mask >> 2 & 15) == 15) ? 15000 : 0;
	if (op == 10) return ((mask & 31) == 31 || (mask >> 1 & 31) == 31) ? 30000 : 0;
	if (op == 11) return b[5] ? 50000 : 0;
	int val = a[op + 1] * (op + 1) * 1000;
	if (!upper_bonus_given && upper_pts_acc < 63000 &&
		upper_pts_acc + val >= 63000) {
		upper_bonus_given = true;
		val += 35000;
	}
	upper_pts_acc += a[op + 1] * (op + 1) * 1000;
	return val;
}

struct Choice {
	int total, s_now, op, nxt_pos, dx, sel_mask10, cur_pos;
};

Choice choose_best_on_10(const vector<int>& v10, int mask, int x) {
	int bestTot = INT_MIN, bestS = 0, bestOp = -1, bestNxt = -1, bestDx = 0, bestSel = 0, bestCur = -1;
	int vv[10];
	for (int i = 0; i < 10; i++) vv[i] = v10[i];
	for (int it = 0; it < 252; ++it) {
		int cur[6]{}, nxt[6]{};
		int m = mask_10C5[it];
		for (int i = 0; i < 10; i++) ((m >> i) & 1 ? cur : nxt)[vv[i] - 1]++;
		int cur_code = 0, nxt_code = 0;
		for (int k = 0; k < 6; k++) {
			cur_code = 6 * cur_code + cur[k];
			nxt_code = 6 * nxt_code + nxt[k];
		}
		int cur_pos = seq_conv[cur_code], nxt_pos = seq_conv[nxt_code];
		for (int op = 0; op <= 11; ++op)
			if (!(mask >> op & 1)) {
				int s = calc_score(op, x, cur_pos);
				int dx = (op <= 5) ? (op + 1) * cur[op] : 0;
				int nx = x + dx;
				if (nx > 63) nx = 63;
				int tot = s + dp[mask | (1 << op)][nxt_pos][nx];
				if (tot > bestTot) {
					bestTot = tot;
					bestS = s;
					bestOp = op;
					bestNxt = nxt_pos;
					bestDx = dx;
					bestSel = m;
					bestCur = cur_pos;
				}
			}
	}
	return {bestTot, bestS, bestOp, bestNxt, bestDx, bestSel, bestCur};
}

pair<int, int> choose_best_on_5(const vector<int>& v5, int mask, int x) {
	int cnt[6]{};
	for (int v : v5) cnt[v - 1]++;
	int code = 0;
	for (int i = 0; i < 6; i++) code = 6 * code + cnt[i];
	int pos = seq_conv[code];
	int bestS = -1, bestOp = -1;
	for (int op = 0; op <= 11; ++op)
		if (!(mask >> op & 1)) {
			int s = calc_score(op, x, pos);
			if (s > bestS) {
				bestS = s;
				bestOp = op;
			}
		}
	return {bestOp, bestS};
}

i64 dp_value_for_pick(char pick, const vector<int>& carry, const vector<int>& A, const vector<int>& B, int mask, int x64) {
	auto conv = [](auto v) {
		int cnt[6]{};
		int val = 0;
		for (int x : v) cnt[x - 1]++;
		for (int i = 0; i < 6; i++) val = 6 * val + cnt[i];
		return seq_conv[val];
	};
	if (pick == 'A') {
		if (carry.empty()) return dp[mask][conv(A)][x64];
		vector<int> v = carry;
		v.insert(v.end(), A.begin(), A.end());
		vector<int> vv = v;
		sort(vv.begin(), vv.end());
		auto C = choose_best_on_10(vv, mask, x64);
		return C.total;
	}
	else {
		if (carry.empty()) return dp[mask][conv(B)][x64];
		vector<int> v = carry;
		v.insert(v.end(), B.begin(), B.end());
		vector<int> vv = v;
		sort(vv.begin(), vv.end());
		auto C = choose_best_on_10(vv, mask, x64);
		return C.total;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	init_seq();
	init_dp();

	int mask_us = 0, x_us = 0, mask_op = 0, x_op = 0;
	vector<int> carry_us, carry_op, lastA, lastB, pend_us, pend_op;
	bool have_pend_us = false, have_pend_op = false;
	i64 score_us = 0, score_op = 0;
	i64 bidbal_us = 0, bidbal_op = 0;
	int upper_us = 0, upper_op = 0;
	bool upper_us_bonus = false, upper_op_bonus = false;
	bool ema_init = false;
	double ema_opp = 800.0;
	const double ema_alpha = 0.30;
	int prv_want = 0; // 0:A 1:B
	int prv_bid = 1;

	string line;
	while (getline(cin, line)) {
		if (line.empty()) continue;
		istringstream in(line);
		string cmd; in >> cmd;
		if (cmd == "READY") {
			cout << "OK" << endl;
		}
		else if (cmd == "ROLL") {
			string a, b; in >> a >> b;
			lastA.clear();
			lastB.clear();
			for (char c : a) lastA.push_back(c - '0');
			for (char c : b) lastB.push_back(c - '0');
			sort(lastA.begin(), lastA.end());
			sort(lastB.begin(), lastB.end());
			i64 UA = dp_value_for_pick('A', carry_us, lastA, lastB, mask_us, x_us);
			i64 UB = dp_value_for_pick('B', carry_us, lastA, lastB, mask_us, x_us);
			i64 OA = dp_value_for_pick('A', carry_op, lastA, lastB, mask_op, x_op);
			i64 OB = dp_value_for_pick('B', carry_op, lastA, lastB, mask_op, x_op);
			char pick_us = (UA >= UB ? 'A' : 'B');
			char pick_op = (OA >= OB ? 'A' : 'B');
			
			// --- after computing UA, UB, OA, OB and pick_us/pick_op ---

			// 1) 마진(현재 코드 기준: UA/UB가 이미 ×1000 스케일)
			i64 du = llabs(UA - UB);  // our margin (×1000)
			i64 dv = llabs(OA - OB);  // opp margin (×1000)

			auto sigmoid = [](double z){ return 1.0/(1.0+exp(-z)); };
			double conf_us = sigmoid((du - 12000.0)/4000.0); // >0.5이면 확신 ↑
			double conf_op = sigmoid((dv - 12000.0)/4000.0);

			// 2) 동적 컨테스트 확률
			bool will_contest = (pick_us == pick_op);
			double p_contest = will_contest
			    ? max(0.65, 0.75*conf_op + 0.25*conf_us)            // 같은 선택: 최소 0.65
			    : (1.0 - min(0.95, 0.7*conf_op + 0.3*conf_us));     // 다른 선택이어도 뒤집힘 반영

			// 3) 라운드/리드, cap 재정의
			int round_no = __builtin_popcount(mask_us) + 1;
			i64 lead = (score_us + bidbal_us) - (score_op + bidbal_op);

			// 컨테스트면 상대 마진도 0.3 섞어 cap 완화
			i64 cap = will_contest
			    ? (i64) llround(0.95 * (0.7*du + 0.3*dv))
			    : (i64) llround(0.95 * du);
			cap = max(0LL, min(cap, 120000LL)); // 상한 살짝 완화(10만→12만)

			i64 bid = 1;

			if (!will_contest) {
			    // 비컨테스트 예측: 불확실하면 가드 입찰
			    bool uncertain = (conf_op < 0.85) || (conf_us < 0.85);
			    if (uncertain) {
			        i64 guard = (i64) llround(0.12 * (double)du);
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
			
			    // 환급 모드: 조건 보수화
			    if (lead < -30000 && du < 14000 && p_contest > 0.75 && ema_init && ema_opp > 1500.0) {
			        raw = min((double)cap, max(1.0, ema_opp - 1.0));
			    }
			
			    bid = (i64) llround(raw * lead_mul);
			    bid = max(1LL, min(bid, cap));
			
			    // 초반 바닥 완화
			    if (round_no <= 2) bid = max(bid, 300LL);
			
			    // 동점 방지 살짝(컨테스트에서는 +1)
			    if (p_contest > 0.5) ++bid;
			}

			cout << "BID " << pick_us << " " << bid << endl;
			prv_want = (pick_us=='A'?0:1);
			prv_bid  = (int)bid;
		}
		else if (cmd == "GET") {
			string g, g0;
			int x0; in >> g >> g0 >> x0;
			bool gotA = (g == "A");
			bool oppWantedA = (g0 == "A");
			vector<int> got_us = (gotA ? lastA : lastB);
			vector<int> got_op = (gotA ? lastB : lastA);
			if (carry_us.empty()) {
				carry_us = std::move(got_us);
				have_pend_us = false;
				pend_us.clear();
			}
			else {
				pend_us = std::move(got_us);
				have_pend_us = true;
			}
			if (carry_op.empty()) {
				carry_op = std::move(got_op);
				have_pend_op = false;
				pend_op.clear();
			}
			else {
				pend_op = std::move(got_op);
				have_pend_op = true;
			}
			bool we_wantedA = (prv_want == 0);
			bool we_got_wanted = (we_wantedA ? gotA : !gotA);
			bidbal_us += (we_got_wanted ? -prv_bid : +prv_bid);
			bool opp_gotA = !gotA;
			bool opp_got_wanted = (oppWantedA ? opp_gotA : !opp_gotA);
			bidbal_op += (opp_got_wanted ? -x0 : +x0);
			bool contested = ((we_wantedA && oppWantedA) || (!we_wantedA && !oppWantedA));
			if (contested) {
				if (!ema_init) {
					ema_opp = x0;
					ema_init = true;
				}
				else ema_opp = ema_alpha * x0 + (1.0 - ema_alpha) * ema_opp;
			}
		}
		else if (cmd == "SCORE") {
			if (have_pend_us) {
				vector<int> v10 = carry_us;
				v10.insert(v10.end(), pend_us.begin(), pend_us.end());
				sort(v10.begin(), v10.end());
				auto C = choose_best_on_10(v10, mask_us, x_us);
				string d5;
				d5.reserve(5);
				for (int i = 0; i < 10; i++) if ((C.sel_mask10 >> i) & 1) d5.push_back(char('0' + v10[i]));
				mask_us |= (1 << C.op);
				x_us += C.dx;
				if (x_us > 63) x_us = 63;
				carry_us.clear();
				for (int i = 0; i < 6; i++) {
					int len = seq[C.nxt_pos][i];
					while (len--) carry_us.push_back(i + 1);
				}
				pend_us.clear();
				have_pend_us = false;
				score_us += score_actual_once(C.op, d5, upper_us, upper_us_bonus);
				cout << "PUT " << get_op_name(C.op) << ' ' << d5 << endl;
			}
			else {
				if (carry_us.empty()) {
					cout << "PUT ONE 11111" << endl;
					continue;
				}
				auto [op, _s] = choose_best_on_5(carry_us, mask_us, x_us);
				string d5;
				d5.reserve(5);
				for (int v : carry_us) d5.push_back(char('0' + v));
				mask_us |= (1 << op);
				score_us += score_actual_once(op, d5, upper_us, upper_us_bonus);
				cout << "PUT " << get_op_name(op) << ' ' << d5 << endl;
			}
		}
		else if (cmd == "SET") {
			string name_op, d5; in >> name_op >> d5;
			int op = 0;
			while (get_op_name(op) != name_op) ++op;
			if (op <= 5) {
				int cnt = 0;
				for (char c : d5) if (c - '0' == op + 1) cnt++;
				x_op += (op + 1) * cnt;
				if (x_op > 63) x_op = 63;
			}
			score_op += score_actual_once(op, d5, upper_op, upper_op_bonus);
			mask_op |= (1 << op);
			vector<int> v10 = carry_op;
			if (have_pend_op) {
				v10.insert(v10.end(), pend_op.begin(), pend_op.end());
				have_pend_op = false;
				pend_op.clear();
			}
			sort(v10.begin(), v10.end());
			int need[7]{};
			for (char c : d5) need[c - '0']++;
			vector<int> nxt;
			for (int v : v10) {
				if (need[v] > 0) need[v]--;
				else nxt.push_back(v);
			}
			carry_op = std::move(nxt);
		}
		else if (cmd == "FINISH") {
			break;
		}
	}
}
