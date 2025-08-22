#include <iostream>
using namespace std;

void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    if (a + b >= 2 * c) cout << a + b - 2 * c << '\n';
    else cout << a + b << '\n';
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