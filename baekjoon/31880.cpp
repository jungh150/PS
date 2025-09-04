#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ans += a;
    }

    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        if (b > 0) ans *= b;
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