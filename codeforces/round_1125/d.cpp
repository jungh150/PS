#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> s(n);
    long long mint = 1e10;

    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;

        s[i] = a + b + c;
        if (a == b && b == c) mint = min(mint, a + b + c);
    }

    sort(s.begin(), s.end());

    long long l = -1e10;
    long long r = 1e10;
    while (l < r) {
        long long m = (l + r) / 2;
        long long need = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] >= m) break;
            need += (m - s[i]);
        }

        if (need > k) l = m;
        else r = m + 1;
    }

    cout << min(l - 1, mint) << '\n';
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