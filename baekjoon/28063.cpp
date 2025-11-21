#include <iostream>
using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    if (n == 1) cout << 0 << '\n';
    else if ((x == 1 || x == n) && (y == 1 || y == n)) cout << 2 << '\n';
    else if ((x == 1 || x == n) || (y == 1 || y == n)) cout << 3 << '\n';
    else cout << 4 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}