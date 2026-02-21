#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    int ans = 0;
    ans += 2 * e;

    int tmp1 = a + 2 * b;
    int tmp2 = c + 2 * d;
    int tmp3 = min(tmp1, tmp2);

    if (((tmp1 - tmp3) % 2 == 1 && a == 0) || (tmp2 - tmp3) % 2 == 1 && c == 0) {
        tmp3--;
    }

    ans += 2 * tmp3;
    if (tmp3 > 0) ans += 2 * f;

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