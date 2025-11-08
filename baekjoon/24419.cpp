#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n + 1; i++) dp[i][0] = 1;
    for (int j = 0; j < n + 1; j++) dp[0][j] = 1;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            dp[i][j] += dp[i - 1][j];
            dp[i][j] += dp[i][j - 1];
        }
    }

    cout << dp[n][n] << ' ' << n * n << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}