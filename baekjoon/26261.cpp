#include <iostream>
#include <vector>
using namespace std;

int MAXVAL = 1e9;
int n, x, k;

struct SegTree {
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = min(update(idx * 2, l, m, target, val), update(idx * 2 + 1, m + 1, r, target, val));
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return MAXVAL;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return min(query(idx * 2, l, m, wl, wr), query(idx * 2 + 1, m + 1, r, wl, wr));
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

    cin >> n >> x >> k;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<bool> chk(n + 1, false);
    int cnt = 0;
    for (int i = 1; i < n + 1; i++) {
        if (a[i] == 0) {
            cnt++;
            if (cnt >= k) chk[i] = true;
        } else {
            cnt = 0;
        }
    }

    SegTree seg;
    seg.tree.assign(4 * n + 1, MAXVAL);
    seg.update(0, 0);

    for (int i = 1; i < n; i++) {
        if (!chk[i]) continue;
        long long mint = seg.query(max(i - x, 0), max(i - k, 0));
        if (mint != MAXVAL) seg.update(i, mint + 1);
    }
    long long mint = seg.query(max(n - x, 0), max(n - 1, 0));
    if (mint != MAXVAL) cout << mint + 1 << '\n';
    else cout << -1 << '\n';
}