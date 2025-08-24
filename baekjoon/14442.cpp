#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;
vector<vector<bool>> g;
vector<vector<vector<bool>>> chk;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void solve() {
    cin >> n >> m >> k;
    g = vector<vector<bool>>(n, vector<bool>(m, 0));
    chk = vector<vector<vector<bool>>>(n, vector<vector<bool>>(m, vector<bool>(k + 1, 0)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            g[i][j] = (c == '1');
        }
    }

    queue<vector<int>> q;
    // {x index, y index, breakCount, count}
    q.push({0, 0, 0, 1});
    chk[0][0][0] = true;
    int ans = -1;
    while (!q.empty()) {
        int curi = q.front()[0];
        int curj = q.front()[1];
        int breakcnt = q.front()[2];
        int cnt = q.front()[3];
        if (curi == n - 1 && curj == m - 1) {
            ans = cnt;
            break;
        }
        q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int nxti = curi + dx[dir];
            int nxtj = curj + dy[dir];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m) {
                if (!g[nxti][nxtj] && !chk[nxti][nxtj][breakcnt]) { // 0
                    q.push({nxti, nxtj, breakcnt, cnt + 1});
                    chk[nxti][nxtj][breakcnt] = true;
                } else if (g[nxti][nxtj] && breakcnt < k && !chk[nxti][nxtj][breakcnt + 1]) { // 1
                    q.push({nxti, nxtj, breakcnt + 1, cnt + 1});
                    chk[nxti][nxtj][breakcnt + 1] = true;
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}