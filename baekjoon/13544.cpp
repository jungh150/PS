#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;

struct MergeSortTree {
    vector<vector<int>> tree;

    void build(int idx, int l, int r, vector<int>& arr) {
        if (l == r) {
            tree[idx].push_back(arr[l]);
            return;
        }

        int m = (l + r) / 2;
        build(idx * 2, l, m, arr);
        build(idx * 2 + 1, m + 1, r, arr);

		tree[idx].resize(tree[idx * 2].size() + tree[idx * 2 + 1].size()); 
		merge(tree[idx * 2].begin(), tree[idx * 2].end(), tree[idx * 2 + 1].begin(), tree[idx * 2 + 1].end(), tree[idx].begin());
    }

    int query(int idx, int l, int r, int wl, int wr, int x) {
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx].end() - upper_bound(tree[idx].begin(), tree[idx].end(), x);
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr, x) + query(idx * 2 + 1, m + 1, r, wl, wr, x);
    }
    
    void build(vector<int>& arr) {
        build(1, 0, n, arr);
    }
    
    int query(int wl, int wr, int x) {
        return query(1, 0, n, wl, wr, x);
    }
};

void solve() {
    MergeSortTree seg;

    cin >> n;
    seg.tree.assign(4 * n + 1, vector<int>());

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];
    seg.build(a);

    cin >> m;
    int pre = 0;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        
        int i = a ^ pre;
        int j = b ^ pre;
        int k = c ^ pre;

        pre = seg.query(i, j, k);
        cout << pre << '\n';
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