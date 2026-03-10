#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int ansv = 0;
    int ansc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) continue;

            vector<vector<bool>> vst(n, vector<bool>(m, 0));
            queue<vector<int>> q;

            vst[i][j] = 1;
            q.push({i, j, 1});
            while (!q.empty()) {
                int curi = q.front()[0];
                int curj = q.front()[1];
                int cnt = q.front()[2];
                q.pop();

                if (cnt > ansc) ansv = a[i][j] + a[curi][curj];
                else if (cnt == ansc) ansv = max(ansv, a[i][j] + a[curi][curj]);
                ansc = max(ansc, cnt);

                for (int k = 0; k < 4; k++) {
                    int nxti = curi + dx[k];
                    int nxtj = curj + dy[k];
                    if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && !vst[nxti][nxtj] && a[nxti][nxtj] != 0) {
                        vst[nxti][nxtj] = 1;
                        q.push({nxti, nxtj, cnt + 1});
                    }
                }
            }
        }
    }

    cout << ansv << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}