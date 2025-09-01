#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, a, b, c;
    cin >> n >> a >> b >> c;

    long long tmp1 = n * (a * b * c - a * b - b * c - c * a);
    long long tmp2 = a * b + b * c + c * a;

    if (tmp1 < 0) {
        cout << -1 << '\n';
        return;
    }
    if (tmp1 % tmp2 != 0) {
        cout << -1 << '\n';
        return;
    }

    long long k = tmp1 / tmp2;
    if (((n + k) % a == 0) && ((n + k) % b == 0) && ((n + k) % c == 0)) {
        cout << k << '\n';
    } else {
        cout << -1 << '\n';
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