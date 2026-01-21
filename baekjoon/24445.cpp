#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void solve() {
    int n, m, r;
    cin >> n >> m >> r;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i < n + 1; i++) {
        sort(adj[i].begin(), adj[i].end(), greater<>());
    }

    vector<int> vst(n + 1, -1);
    queue<int> q;
    int cnt = 1;
    vst[r] = cnt++;
    q.push(r);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt: adj[cur]) {
            if (vst[nxt] == -1) {
                vst[nxt] = cnt++;
                q.push(nxt);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (vst[i] == -1) cout << 0 << '\n';
        else cout << vst[i] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}