#include <iostream>
#include <vector>
using namespace std;

int n, k;
string s;

struct SegTree {
    vector<vector<long long>> tree;
    vector<int> lazy;

    void init(int idx, int l, int r) {
        if (l == r) {
            tree[idx][s[l] - '0'] = 1;
            return;
        }
        int m = (l + r) / 2;
        init(idx * 2, l, m);
        init(idx * 2 + 1, m + 1, r);
        for (int i = 0; i < 10; i++) tree[idx][i] = tree[idx * 2][i] + tree[idx * 2 + 1][i];
    }

    void push(int idx, int l, int r) {
        int rot = lazy[idx] % 10;
        if (rot == 0) return;

        vector<long long> tmp(10, 0);
        for (int i = 0; i < 10; i++) tmp[(i + rot) % 10] = tree[idx][i];
        tree[idx] = tmp;

        if (l < r) {
            lazy[idx * 2] = (lazy[idx * 2] + rot) % 10;
            lazy[idx * 2 + 1] = (lazy[idx * 2 + 1] + rot) % 10;
        }
        lazy[idx] = 0;
    }

    void update(int idx, int l, int r, int wl, int wr, long long val) {
        push(idx, l, r);
        if (wr < l || wl > r) return;
        if (wl <= l && wr >= r) {
            lazy[idx] = (lazy[idx] + val) % 10;
            push(idx, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(idx * 2, l, m, wl, wr, val);
        update(idx * 2 + 1, m + 1, r, wl, wr, val);
        for (int i = 0; i < 10; i++) tree[idx][i] = tree[idx * 2][i] + tree[idx * 2 + 1][i];
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) {
            long long sumt = 0;
            for (int i = 0; i < 10; i++) sumt += 1LL * i * tree[idx][i];
            return sumt;
        }
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    void update(int wl, int wr, long long val) {
        return update(1, 1, n, wl, wr, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
};

void solve() {
    SegTree seg;

    cin >> n >> k;
    seg.tree.assign(4 * n + 1, vector<long long>(10, 0));
    seg.lazy.assign(4 * n + 1, 0);

    string tmp;
    cin >> tmp;
    s = " " + tmp;
    seg.init(1, 1, n);

    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << seg.query(a, b) << '\n';
        seg.update(a, b, 1);
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