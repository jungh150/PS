#include <iostream>
using namespace std;

void solve() {
    int n, x;
    cin >> n >> x;
    int ans = -1;
    for (int i = 0; i < n; i++) {
        int s, t;
        cin >> s >> t;
        if (s + t <= x) {
            ans = max(ans, s);
        }
    }
    cout << ans << '\n';
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