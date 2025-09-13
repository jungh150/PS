#include <bits/stdc++.h>
using namespace std;

int mod = 1000000007; 

void solve() {
    int k, n;
    cin >> k >> n;

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = i;
        int tmp = 1;
        while (x > 0) {
            int rem = x % 10;

            if (rem != k) {
                ans += rem * tmp;
                ans = ans % mod;
                tmp *= 10;
            }

            x /= 10;
        }
    }

    cout << ans << '\n';
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