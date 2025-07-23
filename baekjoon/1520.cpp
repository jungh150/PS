#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m;
vector<vector<int>> a;
vector<vector<int>> dp;
// dp[i][j]: (i, j)에서 목적지까지 갈 수 있는 경우의 수

int dfs(int curi, int curj) {
    if (curi == n - 1 && curj == m - 1) return 1;
    if (dp[curi][curj] == -1) {
        dp[curi][curj] = 0;
        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && a[nxti][nxtj] < a[curi][curj]) {
                dp[curi][curj] += dfs(nxti, nxtj);
            }
        }
    }
    return dp[curi][curj];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    a = vector<vector<int>>(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    dp = vector<vector<int>>(n, vector<int>(m, -1));

    cout << dfs(0, 0) << '\n';
}