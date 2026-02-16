#include <bits/stdc++.h>
using namespace std;

int n, m;

struct SegTree {
    vector<long long> tree;
    vector<bool> lazy;

    void push(int idx, int l, int r) {
        if (lazy[idx] == 0) return;
        tree[idx] = 1;
        if (l < r) {
            lazy[idx * 2] = 1;
            lazy[idx * 2 + 1] = 1;
        }
        lazy[idx] = 0;
    }

    long long update(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return tree[idx];
        if (wl <= l && wr >= r) {
            lazy[idx] = 1;
            push(idx, l, r);
            return tree[idx];
        }
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, wl, wr) + update(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    long long update(int wl, int wr) {
        return update(1, 1, n, wl, wr);
    }
    
    long long query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
};

void solve() {
    int num = 500001;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i * i <= num; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) {
                p[j] = 0;
            }
        }
    }

    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    SegTree seg;
    seg.tree.assign(4 * n + 1, 0);
    seg.lazy.assign(4 * n + 1, 0);

    while (m--) {
        long long a, b;
        cin >> a >> b;
        seg.update(a, b);
    }

    double ans = 0;
    for (int i = 1; i < n + 1; i++) {
        if (seg.query(i, i) > 0) {
            long long sumt = 0;
            int cnt = 0;
            int tmp = a[i];
            for (int j = 2; j * j <= tmp; j++) {
                if (p[j] == 1 && tmp % j == 0) {
                    sumt += j;
                    cnt++;
                }
                while (tmp % j == 0) tmp /= j;
            }
            if (tmp > 1) {
                sumt += tmp;
                cnt++;
            }
            ans += (double) sumt / cnt;
        } else {
            ans += a[i];
        }
    }

    cout << fixed;
    cout.precision(12);
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