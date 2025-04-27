#include <iostream>
#include <vector>
using namespace std;

int n, m;

struct SegTree {
    vector<int> arr;
    vector<int> tree;

    int update(int idx, int l, int r, int target, int val) {
        if (target < l || target > r) return tree[idx];
        if (l == r) {
            arr[target] = val;
            return tree[idx] = l;
        }
        
        int mid = (l + r) / 2;
        int lidx = update(idx * 2, l, mid, target, val);
        int ridx = update(idx * 2 + 1, mid + 1, r, target, val);

        if (lidx == -1) return tree[idx] = ridx;
        if (ridx == -1) return tree[idx] = lidx;

        if (arr[lidx] < arr[ridx]) return tree[idx] = lidx;
        else if (arr[lidx] > arr[ridx]) return tree[idx] = ridx;
        else return tree[idx] = min(lidx, ridx);
    }
    
    int query(int idx, int l, int r, int wl, int wr) {
        if (wr < l || wl > r) return -1;
        if (wl <= l && wr >= r) return tree[idx];

        int mid = (l + r) / 2;
        int lidx = query(idx * 2, l, mid, wl, wr);
        int ridx = query(idx * 2 + 1, mid + 1, r, wl, wr);

        if (lidx == -1) return ridx;
        if (ridx == -1) return lidx;

        if (arr[lidx] < arr[ridx]) return lidx;
        else if (arr[lidx] > arr[ridx]) return ridx;
        else return min(lidx, ridx);
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

    SegTree seg;

    cin >> n;
    seg.arr.resize(n + 1);
    seg.tree.assign(4 * n + 1, -1);

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        seg.update(i, x);
    }

    cin >> m;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (a == 1) seg.update(b, c);
        else if (a == 2) cout << seg.query(b, c) << '\n';
    }
}