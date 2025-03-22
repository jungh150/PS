#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, kn, si, sj;
vector<string> a;
vector<vector<int>> vst;
vector<int> ki;
vector<int> kj;
vector<vector<int>> b;
vector<bool> chk;
int ans = -1;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void bfs(int kt) {
    int i = ki[kt];
    int j = kj[kt];

    vst = vector<vector<int>>(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    q.emplace(i, j);
    vst[i][j] = 0;

    while (!q.empty()) {
        int curi = q.front().first;
        int curj = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < m && a[nxti][nxtj] != 'X' && vst[nxti][nxtj] < 0) {
                q.emplace(nxti, nxtj);
                vst[nxti][nxtj] = vst[curi][curj] + 1;
            }
        }
    }

    for (int k = 0; k < kn; k++) {
        if (ki[k] == si && kj[k] == sj) continue;
        b[kt][k] = vst[ki[k]][kj[k]];
    }
}

void dfs(int cur, int cnt, int time) {
    if (cnt == 5) {
        if (ans == -1) ans = time;
        else ans = min(ans, time);
    } else if (cnt < 5) {
        for (int nxt = 0; nxt < kn - 1; nxt++) {
            if (!chk[nxt] && b[cur][nxt] != -1) {
                chk[nxt] = 1;
                dfs(nxt, cnt + 1, time + b[cur][nxt]);
                chk[nxt] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    a = vector<string>(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') {
                si = i;
                sj = j;
            } else if (a[i][j] == 'K') {
                ki.push_back(i);
                kj.push_back(j);
            }
        }
    }

    ki.push_back(si);
    kj.push_back(sj);
    kn = ki.size();

    b = vector<vector<int>>(kn, vector<int>(kn, -1));

    for (int k = 0; k < kn; k++) bfs(k);

    chk = vector<bool>(kn, 0);
    dfs(kn - 1, 0, 0);

    cout << ans << '\n';
}