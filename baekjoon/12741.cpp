#include <iostream>
#include <vector>
using namespace std;

int MAXVAL = 1e9 + 1;
int n, m;
vector<int> a;

struct SegTree {
    vector<int> tree;

    int update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) return tree[idx] = val;
        int m = (l + r) / 2;
        return tree[idx] = min(update(idx * 2, l, m, target, val), update(idx * 2 + 1, m + 1, r, target, val));
    }
    
    int query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return MAXVAL;
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    a = vector<int>(n + 1, 0);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    SegTree seg;
    seg.tree.assign(4 * n + 1, 0);

    for (int i = 1; i < n; i++) {
        if (a[i] <= a[i + 1]) seg.update(i, 1);
        else seg.update(i, 0);
    }
    seg.update(n, 1);

    while (m--) {
        int q, l, r;
        cin >> q >> l >> r;

        if (q == 1) {
            if (l == r) cout << "CS204\n";
            else if (seg.query(l, r - 1) == 1) cout << "CS204\n";
            else cout << "HSS090\n";
        } else if (q == 2) {
            swap(a[l], a[r]);

            if (l - 1 >= 1) {
                if (a[l - 1] <= a[l]) seg.update(l - 1, 1);
                else seg.update(l - 1, 0);
            }
            if (l + 1 < n + 1) {
                if (a[l] <= a[l + 1]) seg.update(l, 1);
                else seg.update(l, 0);
            }

            if (r - 1 >= 1) {
                if (a[r - 1] <= a[r]) seg.update(r - 1, 1);
                else seg.update(r - 1, 0);
            }
            if (r + 1 < n + 1) {
                if (a[r] <= a[r + 1]) seg.update(r, 1);
                else seg.update(r, 0);
            }
        }
    }
}