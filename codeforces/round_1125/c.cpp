#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> s(n - 4);
    map<int, int> m;
    for (int i = 0; i < n - 4; i++) {
        s[i] = a[i] + a[i + 2] - a[i + 4];
        m[s[i]]++;
    }

    long long ans = 0;
    for (int i = 0; i < n - 4; i++) {
        int cnt = 0;
        for (int j = -4; j <= 4; j += 2) {
            if (i + j < 0 || i + j >= n - 4) continue;
            if (s[i] == s[i + j]) cnt++;
        }
        ans += (m[s[i]] - cnt);
    }

    cout << ans / 2 << '\n';
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