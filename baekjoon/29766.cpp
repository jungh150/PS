#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int n = s.size();
    int ans = 0;
    for (int i = 0; i <= n - 4; i++) {
        if (s.substr(i, 4) == "DKSH") ans++;
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