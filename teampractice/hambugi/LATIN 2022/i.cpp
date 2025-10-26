#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int r, c;
vector<vector<int>> a;

int fd(int x, int y) {
    priority_queue<vector<int>> q;
    int res = 0;
    vector<vector<bool>> vst(r, vector<bool>(c, 0));
    
    int nownum = a[x][y];
    q.push({-nownum, x, y});
    vst[x][y] = true;

    while (!q.empty()) {
        int nowval = -q.top()[0];
        int curi = q.top()[1];
        int curj = q.top()[2];
        q.pop();

        if (nownum <= nowval) {
            nownum = nowval;
            res++;
            for (int k = 0; k < 4; k++) {
                int nxti = curi + dx[k];
                int nxtj = curj + dy[k];
                if (nxti >= 0 && nxti < r && nxtj >= 0 && nxtj < c && !vst[nxti][nxtj]) {
                    q.push({-a[nxti][nxtj], nxti, nxtj});
                    vst[nxti][nxtj] = true;
                }
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