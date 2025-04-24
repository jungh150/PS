#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n, m, k;
vector<long long> arr;
vector<long long> tree;

long long init(int idx, int l, int r) {
    if (l == r) return tree[idx] = arr[l];
    int m = (l + r) / 2;
    return tree[idx] = init(idx * 2, l, m) + init(idx * 2 + 1, m + 1, r);
}

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
    return update(1, 1, n, target, val);
}

long long query(int wl, int wr) {
    return query(1, 1, n, wl, wr);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    int tc = m + k;

    tree.assign(4 * n + 1, 0);
    arr.resize(n + 1);

    for (int i = 1; i < n + 1; i++) cin >> arr[i];

    init(1, 1, n);

    while (tc--) {
        long long a, b, c;
        cin >> a >> b >> c;

        if (a == 1) update(b, c);
        else if (a == 2) cout << query(b, c) << '\n';
    }
}