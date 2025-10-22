#include <iostream>
using namespace std;

void solve() {
    int x, n;
    cin >> x >> n;

    if (n == 0) {
        if (x > 0) cout << "INFINITE\n";
        else cout << 0 << '\n';
    } else if (n == 1) {
        if (x < 0) cout << "INFINITE\n";
        else cout << 0 << '\n';
    } else if (n % 2 == 1) {
        cout << "ERROR\n";
    } else {
        if (x <= 0) {
            cout << 0 << '\n';
        } else {
            int cnt = n / 2;
            cout << (x - 1) / cnt << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}