#include <bits/stdc++.h>
using namespace std;

void solve() {
    string role, s;
    int n;
    cin >> role >> n >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') cout << "B";
        else cout << "R";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}