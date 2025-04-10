#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, ans;
vector<vector<int>> a;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int bfs() {
    queue<pair<int, int>> q;
    vector<vector<bool>> vst(n, vector<bool>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 2) {
                q.emplace(i, j);
                vst[i][j] = 1;
                while (!q.empty()) {
                    int curi = q.front().first;
                    int curj = q.front().second;
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nxti = curi + dx[k];
                        int nxtj = curj + dy[k];
                        if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && a[nxti][nxtj] != 1 && !vst[nxti][nxtj]) {
                            q.emplace(nxti, nxtj);
                            vst[nxti][nxtj] = 1;
                        }
                    }
                }
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vst[i][j] && a[i][j] == 0) cnt++;
        }
    }
    
    return cnt;
}

void dfs(int cnt, int curi, int curj) {
    if (cnt == 3) {
        ans = max(ans, bfs());
    } else {
        int j = curj + 1;
        for (int i = curi; i < n; i++) {
            while (j < m) {
                if (a[i][j] == 0) {
                    a[i][j] = 1;
                    dfs(cnt + 1, i, j);
                    a[i][j] = 0;
                }
                j++;
            }
            j = 0;
        }
    }
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

    dfs(0, 0, -1);

    cout << ans << '\n';
}