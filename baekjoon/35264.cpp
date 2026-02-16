#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> dif(4, 0);
    vector<vector<ll>> ans;
    for (int i = 0; i < n; i++) {
        ll cur = a[i] + dif[i % 4];
        if (cur > 0) {
            ans.push_back({i + 1, cur, 3});
            dif[i % 4] -= cur;
            dif[(i + 2) % 4] += cur;
        } else if (cur < 0) {
            ans.push_back({i + 1, -cur, 1});
            dif[i % 4] -= cur;
            dif[(i + 2) % 4] += cur;
        }
    }

    int sz = ans.size();
    cout << sz << '\n';
    for (int i = 0; i < sz; i++) {
        cout << ans[i][0] << ' ' << ans[i][1] << ' ' << ans[i][2] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}