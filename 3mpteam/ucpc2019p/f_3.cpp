#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<double>> dp(n + 1, vector<double>(4, 0));

    double ans = 0;

    dp[1][0] = (double) 5 / 6;
    dp[1][1] = (double) 1 / 6;

    for (int i = 2; i < n + 1; i++) {
        dp[i][0] = dp[i - 1][0] * 5 / 6;
        dp[i][1] = dp[i - 1][0] * 1 / 6;
        dp[i][2] = dp[i - 1][1] * 1 / 6;
        dp[i][3] = dp[i - 1][2] * 1 / 6;
        ans += dp[i][3] * 16000;
    }

    ans += 1155.0925925926;

    cout << fixed;
    cout.precision(10);

    cout << dp[n][3] * 16000 << '\n';
    cout << ans << '\n';
}