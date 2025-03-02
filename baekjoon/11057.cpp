#include <iostream>
#include <vector>
using namespace std;

int MOD = 10007;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> dp(n + 1, vector<int>(11, 0));

    // dp 배열 초기화
    for (int j = 1; j < 11; j++) dp[1][j] = 1;

    for (int i = 2; i < n + 1; i++) {
        for (int j = 0; j < 11; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j] += dp[i - 1][k];
                dp[i][j] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int j = 1; j < 11; j++) {
        ans += dp[n][j];
        ans %= MOD;
    }
    cout << ans << '\n';
}