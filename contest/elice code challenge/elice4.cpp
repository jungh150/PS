#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int n;
vector<vector<int>> g;
vector<int> dp;
vector<bool> vst;

int dfs(int cur) {
    if (vst[cur]) return dp[cur];
    vst[cur] = true;

    int cnt = 0;
    for (int nxt: g[cur]) {
        if (!vst[nxt]) {
            cnt++;
            dp[cur] = max(dp[cur], cur - dfs(nxt));
        }
    }

    if (cnt == 0) { // 리프 노드라면
        dp[cur] = cur;
        vst[cur] = true;
    }

    return dp[cur];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    g = vector<vector<int>>(n + 1, vector<int>());
    vst = vector<bool>(n + 1);
    dp = vector<int>(n + 1, INT_MIN);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);

    for (int i = 1; i < n + 1; i++) {
        if (dp[i] >= 0) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}