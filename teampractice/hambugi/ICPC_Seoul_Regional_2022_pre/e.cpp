#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, b, a;
    cin >> n >> b >> a;

    vector<long long> arr(n + 1);
    vector<long long> ps(n + 1, 0);

    for (int i = 1; i < n + 1; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    for (int i = 1; i < n + 1; i++) ps[i] = ps[i - 1] + arr[i];

    int l = 0;
    int r = n + 1;
    while (l < r) {
        int m = (l + r) / 2;
        long long tmp = 0;
        if (m - a >= 0) tmp = ps[m - a];
        long long cost = ps[m] - ((ps[m] - tmp) / 2);
        if (cost <= b) l = m + 1;
        else r = m;
    }

    cout << l - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}