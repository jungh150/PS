#include <iostream>
using namespace std;

void solve() {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    if (a > 0) cout << (b - a) * e << '\n';
    else cout << -a * c + d + b * e << '\n';
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