#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> rgb(n + 1, vector<int>(3));
    rgb[0][0] = rgb[0][1] = rgb[0][2] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> rgb[i][0] >> rgb[i][1] >> rgb[i][2];
    }

    vector<vector<int>> dp(n + 1, vector<int>(3));
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    for (int i = 0; i < 3; i++) {
        dp[1][i] = rgb[1][i];
    }

    for (int i = 2; i < n + 1; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
            dp[i][j] += rgb[i][j];
        }
    }

    int ans = 10000000;
    for (int i = 0; i < 3; i++) {
        if (dp[n][i] < ans) {
            ans = dp[n][i];
        }
    }

    cout << ans << '\n';
}