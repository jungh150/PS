#include <iostream>
#include <vector>
using namespace std;

int n, m, si, sj, p, ans;
vector<vector<int>> g;
vector<vector<bool>> vst;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
// 0: down, 1: up, 2: right, 3: left

void dfs(int curi, int curj, int pre, int res) {
    ans = max(ans, res);
    if (curi < 0 || curi >= n || curj < 0 || curj >= m) return;
    if (pre != -1 && vst[curi][curj]) return;

    for (int k = 0; k < 4; k++) {
        int nxti = curi + dx[k];
        int nxtj = curj + dy[k];

        int prevp = p;
        if (pre != -1) {
            if (pre == k) p -= 1;
            else p -= 2;
        }

        if (p >= 0) {
            vst[curi][curj] = true;
            dfs(nxti, nxtj, k, res + g[curi][curj]);
            vst[curi][curj] = false;
        }

        p = prevp; // 원상복구
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    g = vector<vector<int>>(n, vector<int>(m));
    vst = vector<vector<bool>>(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }

    cin >> si >> sj >> p;

    vst[si][sj] = true;
    dfs(si, sj, -1, 0);

    cout << ans << '\n';
}