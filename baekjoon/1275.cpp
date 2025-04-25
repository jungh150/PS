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
        return update(1, 1, n, target, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    SegTree seg;

    cin >> n >> q;
    seg.tree.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        long long x;
        cin >> x;
        seg.update(i, x);
    }

    while (q--) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;

        if (x > y) swap(x, y);
        cout << seg.query(x, y) << '\n';
        seg.update(a, b);
    }
}