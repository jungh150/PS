#include <iostream>
#include <vector>
using namespace std;

int MAX_VAL = 5 * 1e5;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<vector<int>> dp(n + 1, vector<int>(MAX_VAL + 1, 0));
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < MAX_VAL + 1; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j + a[i] < MAX_VAL + 1) dp[i][j] = max(dp[i][j], dp[i - 1][j + a[i]] + a[i]); // 낮은 탑에 올리기
            dp[i][j] = max(dp[i][j], dp[i - 1][abs(j - a[i])]); // 높은 탑에 올리기
        }
    }

    cout << dp[n][0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}