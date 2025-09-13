#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, m, x, y;
    cin >> n >> m >> x >> y;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
    }

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
    }

    cout << n + m << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}