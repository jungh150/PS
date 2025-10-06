#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    if (k >= n) {
        for (int i = 0; i < n; i++) cout << '-';
        cout << '\n';
        return;
    }

    int up = 0;
    int down = 0;
    int up2 = 0;
    int down2 = 0;
    for (char c: s) {
        if (c == '0') {
            up++;
        } else if (c == '1') {
            down++;
        } else if (c == '2') {
            up2++;
            down2++;
        }
    }

    vector<char> ans(n, '+');
    int idx = 0;
    while (up--) {
        ans[idx] = '-';
        idx++;
    }
    while (up2--) {
        if (ans[idx] != '-') ans[idx] = '?';
        idx++;
    }
    idx = n - 1;
    while (down--) {
        ans[idx] = '-';
        idx--;
    }
    while (down2--) {
        if (ans[idx] != '-') ans[idx] = '?';
        idx--;
    }

    for (char c: ans) cout << c;
    cout << '\n';
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