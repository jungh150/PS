#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    long long ans = 0;
    for (int i = 1; i < n; i += 2) {
        ans = max(ans, a[i] - a[i - 1]);
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