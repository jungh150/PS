#include <iostream>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int cnt = 0;
        for (char c: s) {
            if (c == 'O') cnt++;
        }
        if (cnt > m - cnt) ans++;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}