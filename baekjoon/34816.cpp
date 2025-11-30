#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    string s = " ";
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s += c;
    }

    while (q--) {
        int x;
        cin >> x;

        if (x == 1) {
            int i;
            cin >> i;
            if (s[i] == '0') s[i] = '1';
            else s[i] = '0';
        } else if (x == 2) {
            int l, r;
            cin >> l >> r;
            int len = r - l + 1;

            if (len == 1) {
                cout << "NO\n";
            } else if (len == 2) {
                if (s.substr(l, len) == "00" || s.substr(l, len) == "11") cout << "YES\n";
                else cout << "NO\n";
            } else if (len == 3) {
                if (s.substr(l, len) == "010" || s.substr(l, len) == "101") cout << "NO\n";
                else cout << "YES\n";
            } else {
                cout << "YES\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}