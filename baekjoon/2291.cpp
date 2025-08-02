#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    
    // dp[i][j][l]: 합이 i이고 길이가 j이면서 l이상의 수들로만 이루어진 수열의 개수
    vector<vector<vector<long long>>> dp(m + 1, vector<vector<long long>>(n + 1, vector<long long>(m + 1, 0)));

    for (int l = 0; l < m + 1; l++) dp[0][0][l] = 1;

    for (int l = 1; l < m + 1; l++) {
        for (int x = l; x < m + 1; x++) {
            for (int i = x; i < m + 1; i++) {
                for (int j = 1; j < n + 1; j++) {
                    dp[i][j][l] += dp[i - x][j - 1][l];
                }
            }
        }
    }

    int pre = 1;
    for (int i = 1; i < n + 1; i++) { // i: 현재 확정하려는 자리
        for (int j = pre; j <= m - (n - i); j++) {
            if (dp[m - j][n - i][j] >= k) {
                cout << j << ' ';
                m -= j;
                pre = j;
                break;
            } else {
                k -= dp[m - j][n - i][j];
            }
        }
    }
    cout << '\n';
}