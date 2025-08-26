#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<vector<int>>> adj;
int cnt;
vector<int> res;
vector<int> dp;

void dfs(int pre, int cur) {
    for (int i = 0; i < adj[cur].size(); i++) {
        int nxt = adj[cur][i][0];
        int bw = adj[cur][i][1];
        int idx = adj[cur][i][2];
        if (pre == nxt) continue;
        res[idx] = bw;
        if (bw == 1) cnt++; // 역방향이면 +1
        dfs(cur, nxt);
    }
}

void dpf(int pre, int cur) {
    for (int i = 0; i < adj[cur].size(); i++) {
        int nxt = adj[cur][i][0];
        int bw = adj[cur][i][1];
        int idx = adj[cur][i][2];
        if (pre == nxt) continue;
        dp[nxt] = dp[cur];
        if (bw == 1) dp[nxt]--; // 역방향(nxt->cur)이면 -1
        else dp[nxt]++; // 정방향(cur->nxt)이면 +1
        dpf(cur, nxt);
    }
}

void solve() {
    cin >> n;
    // adj[i] = {j, i->j 간선이 역방향인지, i->j 간선의 인덱스}
    adj = vector<vector<vector<int>>>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, 0, i});
        adj[b].push_back({a, 1, i});
    }

    // 임의의 정점에 대해 dfs 수행
    cnt = 0;
    res = vector<int>(n - 1, 0);
    dfs(-1, 1);

    // 그 결과를 기반으로 dp 테이블 채우기
    dp = vector<int>(n + 1, 0);
    dp[1] = cnt;
    dpf(-1, 1);

    // dp 배열에서 최솟값 찾기
    int mint = 1e9;
    int minidx = -1;
    for (int i = 1; i < n + 1; i++) {
        if (dp[i] < mint) {
            mint = dp[i];
            minidx = i;
        }
    }

    // 정답에 대해 dfs 수행
    cnt = 0;
    res = vector<int>(n - 1, 0);
    dfs(-1, minidx);

    for (int x: res) cout << x;
    cout << '\n';
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