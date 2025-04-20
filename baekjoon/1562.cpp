#include <iostream>
#include <vector>
using namespace std;

int mod = 1000000000;
int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(10, vector<int>(1024, 0)));

    for (int j = 1; j < 10; j++) {
        dp[1][j][pow2[j]] = 1;
    }
    
    for (int i = 2; i < n + 1; i++) {
        for (int k = 0; k < 1024; k++) {
            dp[i][0][k | pow2[0]] = (dp[i][0][k | pow2[0]] + dp[i - 1][1][k]) % mod;
            for (int j = 1; j < 9; j++) {
                dp[i][j][k | pow2[j]] = (dp[i][j][k | pow2[j]] + dp[i - 1][j - 1][k]) % mod;
                dp[i][j][k | pow2[j]] = (dp[i][j][k | pow2[j]] + dp[i - 1][j + 1][k]) % mod;

            }
            dp[i][9][k | pow2[9]] = (dp[i][9][k | pow2[9]] + dp[i - 1][8][k]) % mod;
        }
    }

    int ans = 0;
    for (int j = 0; j < 10; j++) ans = (ans + dp[n][j][1023]) % mod;

    cout << ans << '\n';
}