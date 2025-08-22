#include <iostream>
using namespace std;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    int ans = 0;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            for (int k = 1; k <= c; k++) {
                int x = i % j;
                int y = j % k;
                int z = k % i;
                if (x == y && y == z) ans++;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}