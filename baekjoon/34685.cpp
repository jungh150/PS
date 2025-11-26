#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long k;
    cin >> k;

    long long n = 4 * k * k;
    vector<long long> a;
    for (long long x = 1; x < sqrt(n) + 1; x++) {
        if (n % x == 0) {
            if ((x + n/x) % 2 == 0) {
                a.push_back(x);
                a.push_back(n / x);
            }
        }
    }

    long long sz = a.size();
    cout << sz << ' ' << 2 * k * sz << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}