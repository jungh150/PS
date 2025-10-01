#include <iostream>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    if (k == 0) {
        cout << min(n / 2, m) << '\n';
    } else {
        if (n % 2 == 1) {
            n--;
            k--;
        }

        if (n / 2 > m) {
            k -= 2 * (n / 2 - m);
            n -= 2 * (n / 2 - m);
        } else {
            k -= (m - n / 2);
            m -= (m - n / 2);
        }

        if (k <= 0) cout << m << '\n';
        else cout << max(0, m - ((k + 3 - 1) / 3)) << '\n';
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