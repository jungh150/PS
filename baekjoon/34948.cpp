#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first;
    for (int i = 0; i < n; i++) cin >> a[i].second;

    sort(a.begin(), a.end(), greater<>());

    long long len = 0;
    long long maxv = 0;
    for (int i = 0; i < n; i++) {
        len += a[i].second;
        maxv = max(maxv, len * a[i].first);
    }

    cout << maxv;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}