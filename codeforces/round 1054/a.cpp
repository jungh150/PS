#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    long long ans = 0;
    long long cnt = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == -1) cnt++;
        else if (x == 0) ans++;
    }

    if (cnt % 2 == 1) ans += 2;
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