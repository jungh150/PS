#include <iostream>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    int a = 100 - n;
    int b = 100 - m;
    int c = 100 - (a + b);
    int d = a * b;

    int q = d / 100;
    int r = d % 100;

    cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << q << ' ' << r << '\n'; 

    if (q >= 1) cout << c + q << ' ' << r << '\n';
    else cout << c << ' ' << d << '\n';
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