#include <iostream>
#include <vector>
using namespace std;

int n, q;

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val);
    }

    long long query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }

    long long update(int target, long long val) {
        return update(1, 0, n, target, val);
    }

    long long query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

void solve() {
    cin >> n >> q;

    SegTree seg;

    seg.tree.assign(4 * n + 1, 0);

    while (q--) {
        char c;
        cin >> c;

        if (c == '?') {
            int a, b;
            cin >> a >> b;

            long long sum1 = 0;
            long long sum2 = 0;
            if (a < b) {
                sum1 = seg.query(a, b);
                sum2 = seg.query(1, a) + seg.query(b, n);
            } else {
                sum1 = seg.query(b, a);
                sum2 = seg.query(1, b) + seg.query(a, n);
            }
            if (sum1 > 0 && sum2 > 0) cout << "impossible\n";
            else cout << "possible\n";
        } else if (c == '+') {
            int a;
            cin >> a;
            seg.update(a, 0);
        } else if (c == '-') {
            int a;
            cin >> a;
            seg.update(a, 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}