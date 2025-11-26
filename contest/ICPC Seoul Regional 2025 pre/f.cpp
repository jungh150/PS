#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int n = s.size();

    if (n % 2 == 1) {
        cout << -1 << '\n';
        return;
    }

    string ans = "";
    for (int i = 0; i < n; i += 2) {
        char a = s[i];
        char b = s[i + 1];
        if (a == '0') {
            cout << -1 << '\n';
            return;
        }
        if (b == '0' && i == 0) {
            cout << -1 << '\n';
            return;
        }
        if (i >= 2 && b == s[i - 1]) {
            cout << -1 << '\n';
            return;
        }
        for (int j = 0; j < a - '0'; j++) ans += b;
    }
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}