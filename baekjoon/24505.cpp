#include <iostream>
#include <vector>
using namespace std;

int MOD = 1e9 + 7;

struct SegTree {
    int n;
    vector<long long> tree;

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = (update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val)) % MOD;
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return (query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr)) % MOD;
    }
    
    long long update(int target, long long val) {
        return update(1, 0, n, target, val);
    }
    
    long long query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

void solve() {
    int n;
    cin >> n;

    // seg[i]: 길이가 i인 증가 부분수열 개수 저장 (tree[j]: j로 끝나는 증가 부분수열 개수)
    SegTree seg[11];
    for (int i = 0; i < 11; i++) {
        seg[i].n = n;
        seg[i].tree.assign(4 * n + 1, 0);
    }

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;

        seg[0].update(x, seg[0].query(x, x) + 1);
        for (int j = 1; j < 11; j++) {
            long long val = seg[j - 1].query(1, x - 1);
            long long cur = seg[j].query(x, x);
            seg[j].update(x, (cur + val) % MOD);
        }
    }

    cout << seg[10].query(1, n) % MOD << '\n';;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}