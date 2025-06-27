#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    vector<vector<bool>> p(n, vector<bool>(n, false));
    vector<int> dp(n, 10000);

    for (int i = 0; i < n; i++) p[i][i] = true;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) p[i][i + 1] = true;
    }
    for (int i = 2; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (p[j + 1][j + i - 1] && s[j] == s[j + i]) p[j][j + i] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        if (p[0][i]) {
            dp[i] = 1;
        } else {
            for (int k = 0; k < i; k++) {
                if (p[i - k][i]) dp[i] = min(dp[i], dp[i - k - 1] + 1);
            }
        }
    }

    cout << dp[n - 1] << '\n';
}