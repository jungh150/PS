#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b;
    cin >> a >> b;

    if (a % 2 == 1 && b % 2 == 1) {
        cout << a * b + 1 << '\n';
    } else if (a % 2 == 0 && b % 2 == 1) {
        cout << -1 << '\n';
    } else {
        a = (a * b) / 2;
        b = 2;
        if (a % 2 == 0) cout << a + b << '\n';
        else cout << -1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}