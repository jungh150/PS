#include <iostream>
using namespace std;

void solve() {
    int p, m, c, x;
    cin >> p >> m >> c >> x;

    int ans = 1e9 + 100000;
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= c; k++) {
                ans = min(ans, abs((i + j) * (j + k) - x));
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}