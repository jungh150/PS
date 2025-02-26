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

    vector<string> maze(n);
    vector<vector<bool>> vst(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) cin >> maze[i];

    queue<vector<int>> q;
    q.push({0, 0, 1});
    vst[0][0] = true;

    int ans;
    while (!q.empty()) {
        int curx = q.front()[0];
        int cury = q.front()[1];
        int cnt = q.front()[2];
        q.pop();
        if (curx == n - 1 && cury == m - 1) ans = cnt;

        for (int k = 0; k < 4; k++) {
            int nxtx = curx + dx[k];
            int nxty = cury + dy[k];
            if (nxtx >= 0 && nxtx < n && nxty >= 0 && nxty < m && maze[nxtx][nxty] == '1' && !vst[nxtx][nxty]) {
                q.push({nxtx, nxty, cnt + 1});
                vst[nxtx][nxty] = true;
            }
        }
    }

    cout << ans << '\n';
}