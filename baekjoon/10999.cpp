#include <iostream>
#include <vector>
using namespace std;

int n, m, k;

struct SegTree {
    vector<long long> tree;
    vector<long long> lazy;

    void push(int idx, int l, int r) {
        if (lazy[idx] == 0) return;
        tree[idx] += (r - l + 1) * lazy[idx];
        if (l < r) {
            lazy[idx * 2] += lazy[idx];
            lazy[idx * 2 + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    long long update(int idx, int l, int r, int wl, int wr, long long val) {
        push(idx, l, r);
        if (wr < l || wl > r) return tree[idx];
        if (wl <= l && wr >= r) {
            lazy[idx] += val;
            push(idx, l, r);
            return tree[idx];
        }
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, wl, wr, val) + update(idx * 2 + 1, m + 1, r, wl, wr, val);
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    long long update(int wl, int wr, long long val) {
        return update(1, 0, n, wl, wr, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    SegTree seg;

    cin >> n >> m >> k;
    seg.tree.assign(4 * n + 1, 0);
    seg.lazy.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        long long x;
        cin >> x;
        seg.update(i, i, x);
    }

    int q = m + k;
    while (q--) {
        long long a, b, c, d;
        cin >> a;

        if (a == 1) {
            cin >> b >> c >> d;
            seg.update(b, c, d);
        } else if (a == 2) {
            cin >> b >> c;
            cout << seg.query(b, c) << '\n';
        }
    }
}