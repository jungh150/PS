#include <bits/stdc++.h>
using namespace std;

int MAX_VAL = 1e9;

void solve() {
    int n, t, m, s, e;
    cin >> n >> t >> m >> s >> e;

    // adj[i]: {연결된 정점 j, 가중치, 시간 표시}
    vector<vector<vector<int>>> adj(n);

    for (int i = 1; i < t + 1; i++) {
        for (int j = 0; j < m; j++) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a].push_back({b, c, i});
            adj[b].push_back({a, c, i});
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << "i = " << i << '\n';
    //     for (auto nxt: adj[i]) {
    //         cout << nxt[0] << ' ' << nxt[1] << ' ' << nxt[2] << '\n';
    //     }
    // }

    // dst[i][j]: 시간 표기를 j까지 썼을 때 i 정점까지의 거리
    vector<vector<int>> dst(n, vector<int>(t + 1, MAX_VAL));
    // q의 원소: {정점의 dst, 정점, 사용한 시간 표기}
    priority_queue<vector<int>, vector<vector<int>>, greater<>> q;

    dst[s][0] = 0;
    q.push({dst[s][0], s, 0});

    // cout << "-------------\n";
    while (!q.empty()) {
        vector<int> cur = q.top();
        q.pop();
        if (dst[cur[1]][cur[2]] != cur[0]) continue;
        for (auto nxt: adj[cur[1]]) {
            if (nxt[2] <= cur[2]) continue;
            int newdst = cur[0] + nxt[1];
            if (newdst < dst[nxt[0]][nxt[2]]) {
                dst[nxt[0]][nxt[2]] = newdst;
                q.push({newdst, nxt[0], nxt[2]});
                // cout << newdst << ' ' << nxt[0] << ' ' << nxt[2] << '\n';
            }
        }
    }

    int ans = MAX_VAL;
    for (int j = 0; j < t + 1; j++) {
        ans = min(ans, dst[e][j]);
    }

    if (ans == MAX_VAL) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}