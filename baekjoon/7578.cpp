#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int MAX_VAL = 1000000;
int n;

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
        return update(1, 0, MAX_VAL, target, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, MAX_VAL, wl, wr);
    }
};

void solve() {
    cin >> n;

    unordered_map<int, int> pos;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        pos[b[i]] = i;
    }

    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = pos[a[i]];
    }

    SegTree seg;

    seg.tree.assign(4 * MAX_VAL + 1, 0);

    for (int i = 1; i < MAX_VAL + 1; i++) seg.update(i, 0);

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += seg.query(res[i] + 1, MAX_VAL);
        seg.update(res[i], seg.query(res[i], res[i]) + 1);
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}