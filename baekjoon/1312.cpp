#include <iostream>
using namespace std;

void solve() {
    int a, b, n;
    cin >> a >> b >> n;

    int q = 0;
    int r = a;
    for (int i = 0; i < n; i++) {
        r *= 10;
        q = r / b;
        r = r % b;
    }

    cout << q % 10 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}