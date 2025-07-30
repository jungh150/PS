#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> w(n + 1);
    vector<int> v(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> w[i] >> v[i];

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    // dp[i][j]: i번째 물건까지 봤을 때, 무게 j로 얻을 수 있는 최대 가치

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < k + 1; j++) {
            if (j - w[i] >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            else dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][k] << '\n';
}