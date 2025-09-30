#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int r, c;
vector<vector<int>> a;

int fd(int x, int y) {
    int res = 0;
    vector<vector<bool>> vst(r, vector<bool>(c, 0));

    queue<pair<int, int>> q;
    q.emplace(x, y);
    vst[x][y] = true;
    res++;

    while (!q.empty()) {
        auto [curi, curj] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < r && nxtj >= 0 && nxtj < c && !vst[nxti][nxtj] && a[nxti][nxtj] > a[curi][curj]) {
                q.emplace(nxti, nxtj);
                vst[nxti][nxtj] = true;
                res++;
            }
        }
    }

    return res;
}

void solve() {
    cin >> r >> c;
    a = vector<vector<int>>(r, vector<int>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ans = max(ans, fd(i, j));
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}