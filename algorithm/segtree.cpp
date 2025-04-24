#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
int treeHeight, treeSize, leafIndex;
vector<int> arr;
vector<int> tree;

int init(int idx, int l, int r) {
    if (l == r) return tree[idx] = arr[l];
    int m = (l + r) / 2;
    return tree[idx] = init(idx * 2, l, m) + init(idx * 2 + 1, m + 1, r);
}

int update(int idx, int l, int r, int target, int val) {
    if (target < l || target > r) return tree[idx];
    if (l == r) return tree[idx] = val;
    int m = (l + r) / 2;
    return tree[idx] = update(idx * 2, l, m, target, val) + update(idx * 2 + 1, m + 1, r, target, val);
}

int query(int idx, int l, int r, int wl, int wr) {
    if (wr < l || wl > r) return 0;
    if (wl <= l && wr >= r) return tree[idx];
    int m = (l + r) / 2;
    return query(idx * 2, l, m, wl, wr) + query(idx * 2 + 1, m + 1, r, wl, wr);
}

int getMaxArea(int l, int r) {
    //int minidx = query();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    treeHeight = (int)ceil(log2(n)) + 1;
    treeSize = 1 << treeHeight;
    leafIndex = treeSize / 2;
    tree.assign(treeSize, 0);
    arr.resize(n + 1);

    for (int i = 1; i < n + 1; i++) cin >> arr[i];

    init(1, 1, n);

    //
}