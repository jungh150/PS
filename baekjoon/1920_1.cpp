#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> a;

int bs(int target, int start, int end) {
    if (start > end) return -1;

    int mid = (start + end) / 2;

    if (a[mid] == target) return mid;
    else if (a[mid] > target) end = mid - 1;
    else start = mid + 1;

    return bs(target, start, end);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    cin >> m;
    while (m--) {
        int x;
        cin >> x;
        if (bs(x, 0, n - 1) == -1) cout << 0 << '\n';
        else cout << 1 << '\n';
    }
}