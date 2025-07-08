#include <iostream>
#include <vector>
using namespace std;

int n, k;

struct SegTree {
    vector<int> tree;

    int update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, target, val) * update(idx * 2 + 1, m + 1, r, target, val);
    }
    
    int query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return 1;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) * query(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    int update(int target, int val) {
        return update(1, 0, n, target, val);
    }
    
    int query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n >> k) {
        SegTree seg;
        seg.tree.assign(4 * n + 1, 0);

        for (int i = 1; i < n + 1; i++) {
            int x;
            cin >> x;
            if (x > 0) seg.update(i, 1);
            else if (x < 0) seg.update(i, -1);
            else seg.update(i, 0);
        }

        while (k--) {
            char q;
            cin >> q;

            if (q == 'C') {
                int i, v;
                cin >> i >> v;
                if (v > 0) seg.update(i, 1);
                else if (v < 0) seg.update(i, -1);
                else seg.update(i, 0);
            } else if (q == 'P') {
                int i, j;
                cin >> i >> j;
                int res = seg.query(i, j);
                if (res > 0) cout << '+';
                else if (res < 0) cout << '-';
                else cout << '0';
            }
        }
        cout << '\n';
    }
}