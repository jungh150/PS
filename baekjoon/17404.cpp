#include <iostream>
#include <vector>
using namespace std;

int MAXV = 1000 * 1000 + 1;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> rgb(n + 1, vector<int>(3));
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> rgb[i][j];
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(3));
    int ans = MAXV;

    // 첫번째 집이 각각 r, g, b일 때로 나눠서 dp 채우기
    for (int first = 0; first < 3; first++) {
        for (int j = 0; j < 3; j++) {
            if (j == first) dp[1][j] = rgb[1][j];
            else dp[1][j] = MAXV;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][j] = min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
                dp[i][j] += rgb[i][j];
            }
        }

        for (int j = 0; j < 3; j++) {
            if (j != first) ans = min(ans, dp[n][j]);
        }
    }

    cout << ans << '\n';
}