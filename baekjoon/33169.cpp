#include <iostream>
using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;

    cout << 1000 * a + 10000 * b << '\n';
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