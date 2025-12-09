#include <iostream>
#include <algorithm>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    if (n < 0) n = -n;
    if (m < 0) m = -m;

    if (n == 0 && m == 0) cout << 0 << '\n';
    else if ((n == 0 || m == 0) && (n == 1 || m == 1)) cout << 1 << '\n';
    else if (n == 0 || m == 0) cout << 2 << '\n';
    else if (__gcd(n, m) == 1) cout << 1 << '\n';
    else cout << 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}