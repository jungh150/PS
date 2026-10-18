#include <bits/stdc++.h>
using namespace std;

int dp[30][101][101][101];

int td(int r, int a, int b, int c) {
    if (r >= 30 || a < 0 || b < 0 || c < 0) return 0;
    if (dp[r][a][b][c] != -1) return dp[r][a][b][c];
    if (a == 0 && b == 0 && c == 0) return dp[r][a][b][c] = 0;

    int res = -1e9;
    if (a > 0) res = max(res, min(r, a) - td(r + 1, a - min(r, a), b, c)); // a 선택
    if (b > 0) res = max(res, min(r, b) - td(r + 1, a, b - min(r, b), c)); // b 선택
    if (c > 0) res = max(res, min(r, c) - td(r + 1, a, b, c - min(r, c))); // c 선택

    return dp[r][a][b][c] = res;
}

void solve() {
    memset(dp, -1, sizeof(dp));

    int a, b, c;
    cin >> a >> b >> c;

    if (td(1, a, b, c) > 0) cout << "F\n";
    else if (td(1, a, b, c) < 0) cout << "S\n";
    else cout << "D\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}