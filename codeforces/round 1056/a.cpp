#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    long long w = n;
    long long l = 0;

    long long ans = 0;
    while (w >= 2 || l >= 2) {
        long long wpair = w / 2;
        // long long wrest = w - 2 * wpair;
        long long lpair = l / 2;
        // long long lrest = l - 2 * lpair;
        ans += (wpair + lpair);
        w -= wpair;
        l += wpair;
        l -= lpair;
    }

    cout << ans + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}