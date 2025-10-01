#include <iostream>
using namespace std;

void solve() {
    long long a;
    cin >> a;

    int ans = 1;
    while (1) {
        if (a == 1) break;
        if (a % 2 == 0) a = a / 2;
        else a = 3 * a + 1;
        ans++;
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