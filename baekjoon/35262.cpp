#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    int maxc = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            cnt++;
            maxc = max(maxc, cnt);
        } else {
            cnt = 0;
        }
    }

    if (maxc >= k) cout << 0 << '\n';
    else cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}