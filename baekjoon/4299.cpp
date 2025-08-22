#include <iostream>
using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;
    int x = (a + b) / 2;
    int y = a - x;

    if ((a + b) % 2 != 0 || x < 0 || y < 0) cout << -1 << '\n';
    else cout << x << ' ' << y << '\n';
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