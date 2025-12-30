#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
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
    int n;
    cin >> n;

    string s;
    cin >> s;

    SegTree seg; // 동전 앞뒤 변화 횟수 저장
    seg.n = n;
    seg.tree.assign(4 * n + 1, 0);

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) seg.update(i, 0);
        else seg.update(i, 1);
    }

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int i;
            cin >> i;
            if (s[i - 1] == 'H') s[i - 1] = 'T';
            else s[i - 1] = 'H';

            if (i - 2 >= 0) {
                if (s[i - 1] == s[i - 2]) seg.update(i - 1, 0);
                else seg.update(i - 1, 1);
            }
            if (i < n) {
                if (s[i] == s[i - 1]) seg.update(i, 0);
                else seg.update(i, 1);
            }
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;

            int cnt;
            if (l <= r - 1) cnt = seg.query(l, r - 1) + 1;
            else cnt = 1;

            if (cnt % 2 == 1) {
                if (s[l - 1] == 'H') cout << "First\n";
                else cout << "Second\n";
            } else {
                if (cnt % 4 == 0) cout << "First\n";
                else cout << "Second\n";
            }
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