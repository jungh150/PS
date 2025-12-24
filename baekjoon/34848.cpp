#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    while (n > 1) {
        if (n % 2 == 1) {
            ans++;
            n = n / 2 + 1;
        } else {
            n = n / 2;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}