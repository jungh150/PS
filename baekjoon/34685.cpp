#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long k;
    cin >> k;

    long long n = 4 * k * k;
    long long cnt = 0;
    for (long long x = 1; x < sqrt(n) + 1; x++) {
        if (n % x == 0) {
            if (abs(n/x - x) % 2 == 0) cnt += 2;
        }
    }

    cout << cnt << ' ' << 2 * k * cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}