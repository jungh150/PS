#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dn[4] = {0, 0, -1, 1};
int dm[4] = {-1, 1, 0, 0};
int m, n, k;
int cnt = 0;
vector<vector<int>> g;

void bfs(vector<int> start) {
    queue<vector<int>> q;
    cnt++;
    q.push(start);
    g[start[0]][start[1]] = 0;
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tn = cur[0] + dn[i];
            int tm = cur[1] + dm[i];
            if (tn >= 0 && tn < n && tm >= 0 && tm < m && g[tn][tm] == 1) {
                q.push({tn, tm});
                g[tn][tm] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int tn;
    cin >> tn;

    for (int t = 0; t < tn; t++) {
        cnt = 0;
        cin >> m >> n >> k;

        g = vector<vector<int>>(n, (vector<int>(m, 0)));

        int x, y;
        for (int i = 0; i < k; i++) {
            cin >> x >> y;
            g[y][x] = 1;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == 1) {
                    bfs({i, j});
                }
            }
        }

        cout << cnt << '\n';
    }
}