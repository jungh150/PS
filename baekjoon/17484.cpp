#include <iostream>
#include <vector>
using namespace std;

int dx[] = {1, 1, 1};
int dy[] = {-1, 0, 1};

int n, m;
vector<vector<int>> a;
vector<vector<vector<int>>> cost;

void solve() {
    cin >> n >> m;

    a = vector<vector<int>>(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    cost = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(4, 10000)));
    
    for (int j = 0; j < m; j++) cost[0][j][3] = a[0][j];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 3; k++) {
                int nxti = i + dx[k];
                int nxtj = j + dy[k];
                if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m) {
                    for (int kk = 0; kk < 4; kk++) {
                        if (k == kk) continue;
                        cost[nxti][nxtj][k] = min(cost[nxti][nxtj][k], cost[i][j][kk] + a[nxti][nxtj]);
                    }
                }
            }
        }
    }

    int ans = 10000;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < 4; k++) {
            ans = min(ans, cost[n - 1][j][k]);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}