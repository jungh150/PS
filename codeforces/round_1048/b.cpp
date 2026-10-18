#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        if (n - 1 - i < 0) break;
        ans += ((long long) a[n - 1 - i] * (m - i));
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}