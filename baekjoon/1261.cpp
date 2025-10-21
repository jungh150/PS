#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void solve() {
    int m, n;
    cin >> m >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> vst(n, vector<int>(m, 100000));
    queue<pair<int, int>> q;

    q.emplace(0, 0);
    vst[0][0] = 0;
    while (!q.empty()) {
        auto [curi, curj] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m) {
                if (a[nxti][nxtj] == '0') { // 빈 방
                    if (vst[curi][curj] < vst[nxti][nxtj]) {
                        q.emplace(nxti, nxtj);
                        vst[nxti][nxtj] = vst[curi][curj];
                    }
                } else { // 벽
                    if (vst[curi][curj] + 1 < vst[nxti][nxtj]) {
                        q.emplace(nxti, nxtj);
                        vst[nxti][nxtj] = vst[curi][curj] + 1;
                    }
                }
            }
        }
    }

    cout << vst[n - 1][m - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}