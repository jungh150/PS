#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, q;

struct SegTree {
    vector<long long> tree;
    vector<long long> lazy;

    void push(int idx, int l, int r) {
        if (lazy[idx] == 0) return;
        tree[idx] *= (1 << lazy[idx]);
        if (l < r) {
            lazy[idx * 2]++;
            lazy[idx * 2 + 1]++;
        }
        lazy[idx] = 0;
    }

    long long update(int idx, int l, int r, int target, long long val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val);
    }

    long long update2(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return tree[idx];
        if (wl <= l && wr >= r) {
            lazy[idx]++;
            push(idx, l, r);
            return tree[idx];
        }
        int m = (l + r) / 2;
        return tree[idx] = update2(idx * 2, l, m, wl, wr) + update2(idx * 2 + 1, m + 1, r, wl, wr);
    }
    
    long long query(int idx, int l, int r, int wl, int wr) {
        push(idx, l, r);
        if (wr < l || wl > r) return 0;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
    }

    long long update(int target, long long val) {
        return update(0, 1, n, target, val);
    }
    
    long long update2(int wl, int wr) {
        return update2(0, 1, n, wl, wr);
    }
    
    long long query(int wl, int wr) {
        return query(0, 1, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    SegTree seg;

    cin >> n;
    seg.tree.assign(4 * n + 1, 0);
    seg.lazy.assign(4 * n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        long long x;
        cin >> x;
        seg.update(i, x);
    }

    cin >> q;

    while (q--) {
        long long q;
        cin >> q;

        if (q == 1) {
            int c, x;
            cin >> c >> x;
            
            // s1 bs
            int s1 = 1;
            long long tmp;
            while (s1 < c) {
            tmp = seg.query(s1, c);
                if (tmp > x) s1 += (c - s1 + 1) / 2;
                else break;
            }

            if (s1 == c) {
                seg.update(s1, seg.query(s1, s1) + x);
            } else {
                seg.update2(s1, c);
                if (s1 - 1 >= 1) seg.update(s1 - 0, seg.query(s1, s1) + x - tmp);
            }

            cout << "s1: " << s1 << '\n';

            // s2 bs
            int s2 = n;
            while (s2 > c + 1) {
                tmp = seg.query(c + 1, s2);
                if (tmp > x) s2 -= (s2 - c - 1 + 1) / 2;
                else break;
            }

            if (s2 == c + 1) {
                seg.update(s2, seg.query(s2, s2) + x);
            } else {
                seg.update2(c + 1, s2);
                if (s2 + 1 <= n) seg.update(s2 + 1, seg.query(s2, s2) + x - tmp);
            }

            cout << "s2: " << s1 << '\n';

        } else if (q == 2) {
            int c;
            cin >> c;
            cout << seg.query(c, c) << '\n';
        }
    }
}