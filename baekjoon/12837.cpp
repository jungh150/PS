#include <iostream>
#include <vector>
using namespace std;

int n, m;

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] += val;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    SegTree seg;

    cin >> n >> m;
    seg.tree.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) seg.update(i, 0);

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int p, x;
            cin >> p >> x;
            seg.update(p, x);
        } else if (op == 2) {
            int p, q;
            cin >> p >> q;
            cout << seg.query(p, q) << '\n';
        }
    }
}