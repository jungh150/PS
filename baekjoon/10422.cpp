#include <iostream>
#include <vector>
using namespace std;

int MAX_LEN = 5000;
int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    vector<vector<int>> dp(MAX_LEN + 1, vector<int>(MAX_LEN + 1, 0));

    dp[1][1] = 1;
    for (int i = 2; i < MAX_LEN + 1; i++) {
        dp[i][0] = dp[i - 1][1];
        for (int j = 1; j < MAX_LEN; j++) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % MOD;
        }
        dp[i][MAX_LEN] = dp[i - 1][MAX_LEN - 1];
    }

    while (t--) {
        int l;
        cin >> l;

        cout << dp[l][0] << '\n';
    }
}