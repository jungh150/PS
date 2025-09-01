#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, m, a, b;
    cin >> n >> m >> a >> b;
    if (m >= 3 * n) {
        cout << 0 << '\n';
    } else {
        long long ans = (3 * n - m) * a + b;
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}