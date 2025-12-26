#include <iostream>
using namespace std;

void solve() {
    int a, t;
    cin >> a >> t;

    cout << max(0, 10 + 2 * (25 - a + t));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}