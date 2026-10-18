#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;

    int curt = 0;
    int curp = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int dift = a[i].first - curt;
        if (curp == a[i].second) {
            if (dift % 2 == 0) ans += dift;
            else ans += (dift - 1);
        } else {
            if (dift % 2 == 0) ans += (dift - 1);
            else ans += dift;
        }
        curt = a[i].first;
        curp = a[i].second;
    }

    int dift = m - curt;
    ans += dift;

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