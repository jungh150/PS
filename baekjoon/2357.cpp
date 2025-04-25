#include <iostream>
#include <vector>
using namespace std;

int MIN_VAL = 0;
int MAX_VAL = 1000000001;
int n, m;

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
        return update(1, 1, n, target, val);
    }
    
    int query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
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
        return update(1, 1, n, target, val);
    }
    
    int query(int wl, int wr) {
        return query(1, 1, n, wl, wr);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    MinSegTree minseg;
    MaxSegTree maxseg;

    cin >> n >> m;
    minseg.tree.assign(4 * n + 1, MAX_VAL);
    maxseg.tree.assign(4 * n + 1, MIN_VAL);

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        minseg.update(i, x);
        maxseg.update(i, x);
    }

    while (m--) {
        int a, b;
        cin >> a >> b;

        cout << minseg.query(a, b) << ' ' << maxseg.query(a, b) << '\n';
    }
}