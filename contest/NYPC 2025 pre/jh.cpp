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
		for (int i = 0; i < 5; i++) mask |= 1 << s[i] - '1';
		if (op == 6) return sum * 1000;
		if (op == 7) return b[4] || b[5] ? sum * 1000 : 0;
		if (op == 8) return b[2] && b[3] || b[5] ? sum * 1000 : 0;
		if (op == 9) return (mask & 15) == 15 || (mask >> 1 & 15) == 15 || (mask >> 2 & 15) == 15 ? 15000 : 0;
		if (op == 10) return (mask & 31) == 31 || (mask >> 1 & 31) == 31 ? 30000 : 0;
		if (op == 11) return b[5] ? 50000 : 0;
		int val = a[op + 1] * (op + 1) * 1000;
		if (score_up < 63000 && score_up + val >= 63000) val += 35000;
		return val;
	}
};

auto gen = [] {
	board f;
	for (int iter = 1; iter <= 13; iter++) {
		if (iter <= 12) {
			string a;
			string b;
			for (int i = 0; i < 5; i++) a.push_back(gen_rand(1, 6) + '0');
			for (int i = 0; i < 5; i++) b.push_back(gen_rand(1, 6) + '0');
			f.roll(a, b);
			int sa = 0;
			int sb = 0;
			for (int i = 0; i < 5; i++) sa += a[i] - '0';
			for (int i = 0; i < 5; i++) sb += b[i] - '0';
			if (sa > sb) f.get(0);
			else f.get(1);
		}
		if (iter >= 2) {
			// auto [op, s] = f.choose_greedy();
			auto [op, s] = f.choose();
			f.put(op, s);
		}
	}
	cout << "OK" << endl;
	return f.get_score();
};

void test() {
	vector v(10, 0);
	for (int i = 0; i < 10; i++) v[i] = gen();
	sort(v.begin(), v.end());
	cout << "score : ";
	for (int i = 0; i < 10; i++) cout << v[i] << ' ';
	cout << endl;
}

int main() {
	board f;
	int prv;
	while (1) {
		string input; getline(cin, input);
		istringstream in(input);
		string cmd; in >> cmd;
		if (cmd == "READY") {
			cout << "OK" << endl;
		}
		else if (cmd == "ROLL") {
			string a, b; in >> a >> b;
			int sa = 0;
			int sb = 0;
			for (int i = 0; i < 5; i++) sa += a[i] - '0';
			for (int i = 0; i < 5; i++) sb += b[i] - '0';
			f.roll(a, b);
			int val = abs(sa - sb) * 300 + prv / 2;
			if (sa > sb) cout << "BID A " << val << endl;
			else cout << "BID B " << val << endl;
		}
		else if (cmd == "GET") {
			string type; in >> type;
			f.get(type == "A" ? 0 : 1);
			in >> type >> prv;
		}
		else if (cmd == "SCORE") {
			auto [op, s] = f.choose();
			f.put(op, s);
			cout << "PUT " << get_op_name(op) << ' ' << s << endl;
		}
		else if (cmd == "SET") {
		}
		else if (cmd == "FINISH") {
			break;
		}
	}
}