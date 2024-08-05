#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<char>> g;
vector<vector<bool>> vst;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    g = vector<vector<char>>(n, vector<char>(m));
    vst = vector<vector<bool>>(n, vector<bool>(m, false));

    int si, sj;
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'I') {
                si = i;
                sj = j;
            }
        }
    }

    queue<pair<int, int>> q;
    q.emplace(si, sj);
    vst[si][sj] = true;
    while (!q.empty()) {
        int curi = q.front().first;
        int curj = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nxti = curi + dx[i];
            int nxtj = curj + dy[i];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m &&
                g[nxti][nxtj] != 'X' && !vst[nxti][nxtj]) {
                    if (g[nxti][nxtj] == 'P') cnt++;
                    q.emplace(nxti, nxtj);
                    vst[nxti][nxtj] = true;
                }
        }
    }

    if (cnt == 0) cout << "TT\n";
    else cout << cnt << '\n';
}