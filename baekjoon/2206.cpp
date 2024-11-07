#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool>(m));
    vector<vector<vector<bool>>> chk(n, vector<vector<bool>>(m, vector<bool>(2, 0)));

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            g[i][j] = (s[j] == '1');
        }
    }

    queue<vector<int>> q;
    // {x index, y index, didBreak, count}
    q.push({0, 0, 0, 1});
    chk[0][0][0] = true;
    int ans = -1;
    while (!q.empty()) {
        int curi = q.front()[0];
        int curj = q.front()[1];
        int didBreak = q.front()[2];
        int cnt = q.front()[3];
        if (curi == n - 1 && curj == m - 1) {
            ans = cnt;
            break;
        }
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m) {
                if (!g[nxti][nxtj] && !chk[nxti][nxtj][didBreak]) { // 0
                    q.push({nxti, nxtj, didBreak, cnt + 1});
                    chk[nxti][nxtj][didBreak] = true;
                } else if (g[nxti][nxtj] && didBreak == 0 && !chk[nxti][nxtj][didBreak + 1]) { // 1
                    q.push({nxti, nxtj, didBreak + 1, cnt + 1});
                    chk[nxti][nxtj][didBreak + 1] = true;
                }
            }
        }
    }

    cout << ans << '\n';
}