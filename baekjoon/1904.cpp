#include <iostream>
#include <vector>
using namespace std;

int MOD = 15746;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> dp(n + 1, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[1][0] = 0;
    dp[1][1] = 1;
    if (n >= 2) {
        dp[2][0] = 1;
        dp[2][1] = 1;
    }

    for (int i = 3; i < n + 1; i++) {
        dp[i][0] = dp[i - 2][0] + dp[i - 2][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
        dp[i][0] %= MOD;
        dp[i][1] %= MOD;
    }

    cout << (dp[n][0] + dp[n][1]) % MOD << '\n';
}