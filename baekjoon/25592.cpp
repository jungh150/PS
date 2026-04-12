#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int cur = 1;
    int ans = 0;

    while (1) {
        // me
        n -= cur;
        if (n == 0) {
            break;
        } else if (n < 0) {
            ans = -n;
            break;
        }
        // you
        n -= (cur + 1);
        if (n == 0) {
            ans = cur + 2;
            break;
        } else if (n < 0) {
            break;
        }
        // next
        cur += 2;
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