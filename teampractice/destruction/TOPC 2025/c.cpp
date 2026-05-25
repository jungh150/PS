#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> sh(n + 1, 0);
    vector<vector<int>> tu(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> tu[i][0] >> tu[i][1] >> tu[i][2];
    }

    for (int i = 0; i < m; i++) {
        ll x = tu[i][0];
        ll y = tu[i][1];
        ll v = tu[i][2];
        
        ll tmpx = sh[y] + v;
        ll tmpy = sh[x] + v;
        sh[x] = max(sh[x], tmpx);
        sh[y] = max(sh[y], tmpy);

        // for (int i = 1; i < n + 1; i++) cout << sh[i] << ' ';
        // cout << '\n';
    }

    for (int i = 1; i < n + 1; i++) cout << sh[i] << ' ';
    cout << '\n';

    ll ans = 0;
    for (int i = 1; i < n + 1; i++) ans = max(ans, sh[i]);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}