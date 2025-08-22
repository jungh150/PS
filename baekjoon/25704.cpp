#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int ans = 8 * (n - 1);
    while (n--) {
        int x;
        cin >> x;
        ans += x;
    }
    cout << ans / 24 << ' ' << ans % 24 << '\n';
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