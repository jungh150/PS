#include <iostream>
#include <vector>
using namespace std;

int n, k;

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val);
    }
    
    long long query(int idx, int l, int r, int k) {
        if (l == r) return l;
        int m = (l + r) / 2;
        long long left = tree[idx * 2];
        if (k <= left) return query(idx * 2, l, m, k);
        else return query(idx * 2 + 1, m + 1, r, k - left);
    }
    
    long long update(int target, long long val) {
        return update(1, 0, n, target, val);
    }
    
    long long query(int k) {
        return query(1, 0, n, k);
    }
};

void solve() {
    SegTree seg;

    cin >> n >> k;
    seg.tree.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) seg.update(i, 1);

    int idx = 0;
    int alive = n;
    cout << "<";
    for (int i = 0; i < n; i++) {
        idx = (idx + k - 1) % alive;
        int tar = seg.query(idx + 1);
        seg.update(tar, 0);
        if (i == n - 1) cout << tar;
        else cout << tar << ", ";
        alive--;
    }
    cout << ">\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}