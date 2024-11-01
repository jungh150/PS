#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> stk(2, vector<int>(n + 1));
        for (int i = 0; i < 2; i++) {
            for (int j = 1; j < n + 1; j++) {
                cin >> stk[i][j];
            }
        }

        vector<vector<int>> dp(2, vector<int>(n + 1, 0));
        dp[0][1] = stk[0][1];
        dp[1][1] = stk[1][1];

        for (int i = 2; i < n + 1; i++) {
            dp[0][i] = max(dp[1][i - 1], dp[1][i - 2]) + stk[0][i];
            dp[1][i] = max(dp[0][i - 1], dp[0][i - 2]) + stk[1][i];
        }

        cout << max(dp[0][n], dp[1][n]) << '\n';
    }
}