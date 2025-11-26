#include <iostream>
using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << (a + b - 1 + c + d - 1) % 4 + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}