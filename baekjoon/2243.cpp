#include <iostream>
#include <vector>
using namespace std;

int n, m;

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
    SegTree seg;

    n = 1e6 + 1;
    cin >> m;
    seg.tree.assign(4 * n + 1, 0);

    while (m--) {
        int a, b, c;
        cin >> a;
        
        if (a == 1) {
            cin >> b;
            int l = 0;
            int r = n;
            while (l < r) {
                int m = (l + r) / 2;
                if (seg.query(0, m) < b) l = m + 1;
                else r = m;
            }
            cout << l << '\n';
            seg.update(l, seg.query(l, l) - 1);
        } else if (a == 2) {
            cin >> b >> c;
            seg.update(b, seg.query(b, b) + c);
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