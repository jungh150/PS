#include <iostream>
#include <vector>
using namespace std;

long long MOD = 1e9 + 7;
int n, m;

struct SegTree {
    vector<long long> tree;
    vector<long long> lazya;
    vector<long long> lazyb;

    void push(int idx, int l, int r) {
        if (lazya[idx] == 1 && lazyb[idx] == 0) return;
        tree[idx] = (tree[idx] * lazya[idx] + (r - l + 1) * lazyb[idx]) % MOD;
        if (l < r) {
            lazya[idx * 2] = (lazya[idx * 2] * lazya[idx]) % MOD;
            lazyb[idx * 2] = (lazya[idx] * lazyb[idx * 2] + lazyb[idx]) % MOD;
            lazya[idx * 2 + 1] = (lazya[idx * 2 + 1] * lazya[idx]) % MOD;
            lazyb[idx * 2 + 1] = (lazya[idx] * lazyb[idx * 2 + 1] + lazyb[idx]) % MOD;
        }
        lazya[idx] = 1;
        lazyb[idx] = 0;
    }

    long long update1(int idx, int l, int r, int wl, int wr, long long val) {
        push(idx, l, r);
        if (wr < l || wl > r) return tree[idx];
        if (wl <= l && wr >= r) {
            lazyb[idx] = (lazyb[idx] + val) % MOD;
            push(idx, l, r);
            return tree[idx];
        }
        int m = (l + r) / 2;
        return tree[idx] = (update1(idx * 2, l, m, wl, wr, val) + update1(idx * 2 + 1, m + 1, r, wl, wr, val)) % MOD;
    }

    long long update2(int idx, int l, int r, int wl, int wr, long long val) {
        push(idx, l, r);
        if (wr < l || wl > r) return tree[idx];
        if (wl <= l && wr >= r) {
            lazya[idx] = (lazya[idx] * val) % MOD;
            lazyb[idx] = (lazyb[idx] * val) & MOD;
            push(idx, l, r);
            return tree[idx];
        }
        int m = (l + r) / 2;
        return tree[idx] = (update2(idx * 2, l, m, wl, wr, val) + update2(idx * 2 + 1, m + 1, r, wl, wr, val)) % MOD;
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return (query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr)) % MOD;
    }
    
    long long update1(int wl, int wr, long long val) {
        return update1(1, 0, n, wl, wr, val);
    }

    long long update2(int wl, int wr, long long val) {
        return update2(1, 0, n, wl, wr, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

void solve() {
    SegTree seg;

    cin >> n;
    seg.tree.assign(4 * n + 1, 0);
    seg.lazya.assign(4 * n + 1, 1);
    seg.lazyb.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        long long x;
        cin >> x;
        seg.update1(i, i, x);
    }

    cin >> m;
    while (m--) {
        int q, x, y;
        long long v;
        cin >> q;
        if (q == 1) {
            cin >> x >> y >> v;
            seg.update1(x, y, v);
        } else if (q == 2) {
            cin >> x >> y >> v;
            seg.update2(x, y, v);
        } else if (q == 3) {
            cin >> x >> y >> v;
            seg.update2(x, y, 0);
            seg.update1(x, y, v);
        } else if (q == 4) {
            cin >> x >> y;
            cout << seg.query(x, y) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}