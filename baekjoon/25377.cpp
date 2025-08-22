#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int ans = 1e6;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a <= b) ans = min(ans, b);
    }
    if (ans == 1e6) cout << -1 << '\n';
    else cout << ans << '\n';
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