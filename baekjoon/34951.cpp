#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, e, g;
vector<vector<int>> edge, adj;
vector<int> s, nearg;
vector<long long> vst;

long long dfs(int cur) {
    if (vst[cur] != -1) return vst[cur];
    long long val = 0;
    for (int nxt: adj[cur]) {
        val = max(val, dfs(nxt));
    }
    if (cur > n) val += s[cur - n];
    return vst[cur] = val;
}

void solve() {
    cin >> n >> m >> e;

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < 0) u = -u + n;
        if (v < 0) v = -v + n;
        edge.push_back({u, v, w});
    }

    s = vector<int>(m + 1);
    for (int i = 1; i < m + 1; i++) cin >> s[i];

    cin >> g;

    adj = vector<vector<int>>(n + m + 1);
    for (int i = 0; i < e; i++) {
        int u = edge[i][0];
        int v = edge[i][1];
        int w = edge[i][2];
        adj[u].push_back(v);
        if (u == g || v == g) nearg.push_back(w);
    }

    vst = vector<long long>(n + m + 1, -1);
    queue<int> q;

    long long res = dfs(1);

    for (int x: nearg) {
        if (x <= res) {
            cout << "HAPPY\n";
            return;
        }
    }
    cout << "SAD\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}