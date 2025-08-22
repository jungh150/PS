#include <iostream>
using namespace std;

void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    if (b < c) cout << a * c / b << '\n';
    else cout << a * b / c << '\n';
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