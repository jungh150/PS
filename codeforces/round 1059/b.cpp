#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') ans.push_back(i + 1);
    }

    cout << ans.size() << '\n';
    for (int x: ans) cout << x << ' ';
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