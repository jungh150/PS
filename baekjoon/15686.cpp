#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m, hn, cn;
int ans = 1000000;
vector<bool> cchk;
vector<vector<int>> sp;

void dfs(int cnt, int idx) {
    if (cnt == m) {
        int res = 0;
        for (int i = 0; i < hn; i++) {
            int tmp = 1000000;
            for (int j = 0; j < cn; j++) {
                if (cchk[j]) {
                    tmp = min(tmp, sp[i][j]);
                }
            }
            res += tmp;
        }
        ans = min(ans, res);
    } else {
        for (int i = idx + 1; i < cn; i++) {
            if (!cchk[i]) {
                cchk[i] = 1;
                dfs(cnt + 1, i);
                cchk[i] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(n));
    vector<pair<int, int>> house;
    vector<pair<int, int>> chicken;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 1) house.emplace_back(i, j);
            else if (a[i][j] == 2) chicken.emplace_back(i, j);
        }
    }

    hn = house.size();
    cn = chicken.size();
    sp = vector<vector<int>>(hn, vector<int>(cn));

    for (int i = 0; i < hn; i++) {
        vector<vector<int>> vst(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        int si = house[i].first;
        int ei = house[i].second;

        vst[si][ei] = 0;
        q.emplace(si, ei);

        while (!q.empty()) {
            int curi = q.front().first;
            int curj = q.front().second;
            q.pop();
            for (int k = 0; k < 4; k++) {
                int nxti = curi + dx[k];
                int nxtj = curj + dy[k];
                if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < n && vst[nxti][nxtj] == -1) {
                    vst[nxti][nxtj] = vst[curi][curj] + 1;
                    q.emplace(nxti, nxtj);
                }
            }
        }

        for (int j = 0; j < cn; j++) {
            sp[i][j] = vst[chicken[j].first][chicken[j].second];
        }
    }

    cchk = vector<bool>(cn, 0);
    dfs(0, -1);

    cout << ans << '\n';
}