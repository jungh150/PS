#include <iostream>
#include <vector>
using namespace std;

int mod = 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> dp(n + 1, vector<int>(10, 0));

    for (int j = 1; j < 10; j++) dp[1][j] = 1;
    
    for (int i = 2; i < n + 1; i++) {
        dp[i][0] = dp[i - 1][1];
        for (int j = 1; j < 9; j++) dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % mod;
        dp[i][9] = dp[i - 1][8];
    }

    int ans = 0;
    for (int j = 0; j < 10; j++) ans = (ans + dp[n][j]) % mod;

    cout << ans << '\n';
}