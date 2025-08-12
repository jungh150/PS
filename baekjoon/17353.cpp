#include <iostream>
#include <vector>
using namespace std;

int n, m;

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

    cin >> n;
    seg.tree.assign(4 * n + 1, 0);
    seg.lazy.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 2; i++) seg.update(i, i, 0);

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    cin >> m;
    while (m--) {
        long long q;
        cin >> q;

        if (q == 1) {
            long long l, r;
            cin >> l >> r;
            seg.update(l, r, 1);
            seg.update(r + 1, r + 1, -(r - l + 1));
        } else if (q == 2) {
            long long x;
            cin >> x;
            cout << a[x] + seg.query(1, x) << '\n';
        }
    }
}