#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> arr;
vector<int> tree;

int init(int idx, int l, int r) {
    if (l == r) return tree[idx] = l;
    int m = (l + r) / 2;

    int lidx = init(idx * 2, l, m);
    int ridx = init(idx * 2 + 1, m + 1, r);

    if (arr[lidx] < arr[ridx]) return tree[idx] = lidx;
    else return tree[idx] = ridx;
}

int query(int idx, int l, int r, int wl, int wr) {
    if (wr < l || wl > r) return -1;
    if (wl <= l && wr >= r) return tree[idx];

    int m = (l + r) / 2;
    int lidx = query(idx * 2, l, m, wl, wr);
    int ridx = query(idx * 2 + 1, m + 1, r, wl, wr);

    if (lidx == -1) return ridx;
    if (ridx == -1) return lidx;

    if (arr[lidx] < arr[ridx]) return lidx;
    else return ridx;
}

int query(int wl, int wr) {
    return query(1, 1, n, wl, wr);
}

long long getMaxArea(int l, int r) {
    if (l > r) return 0;
    int minidx = query(l, r);
    long long maxArea = (long long) arr[minidx] * (r - l + 1);
    return max(maxArea, max(getMaxArea(l, minidx - 1), getMaxArea(minidx + 1, r)));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    tree.assign(4 * n + 1, 0);
    arr.resize(n + 1);

    for (int i = 1; i < n + 1; i++) cin >> arr[i];

    init(1, 1, n);
    
    cout << getMaxArea(1, n) << '\n';
}