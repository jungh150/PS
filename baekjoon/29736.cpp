#include <iostream>
using namespace std;

void solve() {
    int a, b, k, x;
    cin >> a >> b >> k >> x;

    int ans = min(k + x, b) - max(k - x, a) + 1;
    if (ans <= 0) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}