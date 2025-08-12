#include <iostream>
#include <vector>
using namespace std;

int MIN_VAL = 0;
int MAX_VAL = 1000000001;
int n, k;

struct MinSegTree {
    vector<int> tree;

    int update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = min(update(idx * 2, l, m, target, val), update(idx * 2 + 1, m + 1, r, target, val));
    }
    
    int query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return MAX_VAL;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return min(query(idx * 2, l, m, wl, wr), query(idx * 2 + 1, m + 1, r, wl, wr));
    }
    
    int update(int target, int val) {
        return update(1, 0, n, target, val);
    }
    
    int query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

struct MaxSegTree {
    vector<int> tree;

    int update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = max(update(idx * 2, l, m, target, val), update(idx * 2 + 1, m + 1, r, target, val));
    }
    
    int query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return MIN_VAL;
        if (wl <= l && wr >= r) return tree[idx];
        int m = (l + r) / 2;
        return max(query(idx * 2, l, m, wl, wr), query(idx * 2 + 1, m + 1, r, wl, wr));
    }
    
    int update(int target, int val) {
        return update(1, 0, n, target, val);
    }
    
    int query(int wl, int wr) {
        return query(1, 0, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    MinSegTree minseg;
    MaxSegTree maxseg;

    int t;
    cin >> t;
    
    while (t--) {
        cin >> n >> k;

        vector<int> dvd(n);
        minseg.tree.assign(4 * n + 1, MAX_VAL);
        maxseg.tree.assign(4 * n + 1, MIN_VAL);

        for (int i = 0; i < n; i++) {
            dvd[i] = i;
            minseg.update(i, i);
            maxseg.update(i, i);
        }

        while (k--) {
            int q, a, b;
            cin >> q >> a >> b;

            if (q == 0) {
                swap(dvd[a], dvd[b]);
                minseg.update(a, dvd[a]);
                minseg.update(b, dvd[b]);
                maxseg.update(a, dvd[a]);
                maxseg.update(b, dvd[b]);
            } else if (q == 1) {
                if (minseg.query(a, b) == a && maxseg.query(a, b) == b) cout << "YES\n";
                else cout << "NO\n";
            }
        }
    }
}