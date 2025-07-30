#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s1, s2;
    cin >> s1 >> s2;
    
    int n1 = s1.size();
    int n2 = s2.size();

    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    vector<vector<int>> memo(n1 + 1, vector<int>(n2 + 1, 0)); // 1:up, 2:left, 3:diagonal

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                memo[i + 1][j + 1] = 3;
            } else if (dp[i][j + 1] > dp[i + 1][j]) {
                dp[i + 1][j + 1] = dp[i][j + 1];
                memo[i + 1][j + 1] = 1; // up
            } else { // dp[i][j + 1] <= dp[i + 1][j]
                dp[i + 1][j + 1] = dp[i + 1][j];
                memo[i + 1][j + 1] = 2; // left
            }
        }
    }

    // back tracking
    string ans = "";
    int idx1 = n1;
    int idx2 = n2;
    while (idx1 > 0 && idx2 > 0) {
        if (memo[idx1][idx2] == 1) { // up
            idx1--;
        } else if (memo[idx1][idx2] == 2) { // left
            idx2--;
        } else if (memo[idx1][idx2] == 3) {
            ans += s1[idx1 - 1];
            idx1--;
            idx2--;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << dp[n1][n2] << '\n' << ans << '\n';
}