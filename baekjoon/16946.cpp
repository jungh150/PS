#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m, 0));
    vector<vector<int>> ans(n, vector<int>(m, 0));
    vector<int> group(1, 0);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') g[i][j] = -1; // 벽을 -1로 저장
        }
    }

    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != 0) continue; // 벽이거나 이미 그룹화한 칸이라면 패스

            // bfs 수행
            int tmpcnt = 0;
            queue<pair<int, int>> q;
            q.emplace(i, j);
            g[i][j] = cnt; // 방문 표시
            tmpcnt++;
            while (!q.empty()) {
                int curi = q.front().first;
                int curj = q.front().second;
                q.pop();
                for (int k = 0; k < 4; k++) {
                    int nxti = curi + dx[k];
                    int nxtj = curj + dy[k];
                    if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && g[nxti][nxtj] == 0) {
                        q.emplace(nxti, nxtj);
                        g[nxti][nxtj] = cnt; // 방문 표시
                        tmpcnt++;
                    }
                }
            }
            group.push_back(tmpcnt);

            cnt++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != -1) continue; // 벽이 아니면 패스
            ans[i][j]++;
            set<int> tmp;
            for (int k = 0; k < 4; k++) {
                int nxti = i + dx[k];
                int nxtj = j + dy[k];
                if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && g[nxti][nxtj] > 0) {
                    tmp.insert(g[nxti][nxtj]);
                }
            }
            for (int x: tmp) {
                ans[i][j] += group[x];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] % 10;
        }
        cout << '\n';
    }
}