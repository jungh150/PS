#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m;
vector<vector<bool>> g;

bool bfs() {
    vector<vector<bool>> vst(n, vector<bool>(m, false));
    vector<vector<int>> out(n, vector<int>(m, 0));
    bool finish = true;

    queue<pair<int, int>> q;
    q.emplace(0, 0);
    vst[0][0] = true;
    while (!q.empty()) {
        int curi = q.front().first;
        int curj = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nxti = curi + dx[i];
            int nxtj = curj + dy[i];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && !vst[nxti][nxtj]) {
                if (g[nxti][nxtj]) {
                    finish = false;
                    out[nxti][nxtj]++;
                    if (out[nxti][nxtj] >= 2) vst[nxti][nxtj] = true;
                } else {
                    q.emplace(nxti, nxtj);
                    vst[nxti][nxtj] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (out[i][j] >= 2) {
                g[i][j] = false;
            }
        }
    }

    return finish;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    g = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            g[i][j] = x;
        }
    }

    int time = 0;
    bool isFinished = false;
    while (!isFinished) {
        isFinished = bfs();
        time++;
    }
    
    cout << time - 1 << '\n';
}