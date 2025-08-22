#include <iostream>
using namespace std;

void solve() {
    long long n, m;
    cin >> n >> m;
    if (n < m) swap(n, m); // now, n > m
    if (n % 2 == 0 || m % 2 == 0) cout << n * m / 2 << '\n';
    else cout << int(n / 2) * m + int(m / 2) << '\n';
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