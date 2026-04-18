#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

struct MergeSortTree {
    vector<vector<int>> tree;

    void update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return;
        tree[idx].push_back(val);
        if (l == r) return;
        int m = (l + r) / 2;
        update(idx * 2, l, m, target, val);
        update(idx * 2 + 1, m + 1, r, target, val);
    }

    int query(int idx, int l, int r, int wl, int wr, int x) {
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return upper_bound(tree[idx].begin(), tree[idx].end(), x) - tree[idx].begin();
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr, x) + query(idx * 2 + 1, m + 1, r, wl, wr, x);
    }
    
    void update(int target, int val) {
        update(1, 0, n, target, val);
    }
    
    int query(int wl, int wr, int x) {
        return query(1, 0, n, wl, wr, x);
    }
};

void solve() {
    MergeSortTree seg;

    cin >> n >> m;
    seg.tree.assign(4 * n + 1, vector<int>());

    vector<int> a(n + 1);
    vector<int> vals;

    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        seg.update(i, a[i]);
        vals.push_back(a[i]);
    }

    sort(vals.begin(), vals.end());

    for (int i = 1; i <= 4 * n; i++) sort(seg.tree[i].begin(), seg.tree[i].end());

    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;

        int l = 0;
        int r = vals.size();
        while (l < r) {
            int mid = (l + r) / 2;
            if (seg.query(i, j, vals[mid]) < k) l = mid + 1;
            else r = mid;
        }
        cout << vals[l] << '\n';
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