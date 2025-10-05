#include <iostream>
#include <vector>
using namespace std;

int n, m;
int MAX_VAL = 1e6;

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
    SegTree seg;

    cin >> n >> m;
    seg.tree.assign(4 * MAX_VAL + 1, 0);

    vector<int> idx(n + 1, -1);
    int cur = MAX_VAL;

    for (int i = n; i >= 1; i--) {
        idx[i] = cur;
        seg.update(idx[i], 1);
        cur--;
    }

    while (m--) {
        int x;
        cin >> x;
        cout << seg.query(0, idx[x] - 1) << ' ';
        seg.update(idx[x], 0); // 원래는 0으로
        idx[x] = cur;
        cur--;
        seg.update(idx[x], 1); // 새로운 건 1으로
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}