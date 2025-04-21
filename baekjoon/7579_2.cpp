#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> mem(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> mem[i];

    vector<int> c(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> c[i];

    vector<vector<int>> dp(10001, vector<int>(n + 1, 0));

    for (int i = 0; i < 10001; i++) {
        for (int j = 1; j < n + 1; j++) {
            dp[i][j] = dp[i][j - 1];
            if (i - c[j] >= 0) dp[i][j] = max(dp[i][j], dp[i - c[j]][j - 1] + mem[j]);
        }
    }

    for (int i = 0; i < 10001; i++) {
        if (dp[i][n] >= m) {
            cout << i << '\n';
            return 0;
        }
    }
}