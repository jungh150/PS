#include <iostream>
using namespace std;

void solve() {
    int a, k;
    cin >> a >> k;

    if (k == 0 || a % 2 == 1) cout << a << '\n';
    else cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}