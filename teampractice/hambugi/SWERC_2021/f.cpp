#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    int rcnt = 0;
    int wcnt = 0;
    for (int i = 0; i < m; i++) {
        int r, w;
        cin >> r >> w;
        rcnt = max(rcnt, r);
        wcnt = max(wcnt, w);
    }

    if (rcnt + wcnt > n) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    for (int i = 0; i < rcnt; i++) cout << 'R';
    for (int i = 0; i < wcnt; i++) cout << 'W';
    for (int i = 0; i < n - rcnt - wcnt; i++) cout << 'W';
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