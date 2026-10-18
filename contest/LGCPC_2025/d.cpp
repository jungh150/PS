#include <bits/stdc++.h>
using namespace std;

int n;
vector<long long> a;
vector<long long> b;
vector<vector<pair<int, int>>> adj;

int bfs(int cur, long long tlimit) {
    int vst = 0;
    queue<pair<int, long long>> q;
    long long time = 0;
    q.emplace(cur, time);
    vst |= (1 << cur);
    while (!q.empty()) {
        cur = q.front().first;
        time = q.front().second;
        q.pop();
        for (auto [nxt, w]: adj[cur]) {
            if (!(vst & (1 << nxt)) && (time + w <= tlimit)) {
                q.emplace(nxt, time + w);
                vst |= (1 << nxt);
            }
        }
    }
    return vst;
}

void solve() {
    cin >> n;

    a = vector<long long>(n + 1);
    b = vector<long long>(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i] >> b[i];

    adj = vector<vector<pair<int, int>>>(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> bm(n + 1);
    for (int i = 1; i < n + 1; i++) {
        bm[i] = bfs(i, b[i]);
    }

    long long ans = 1e15;
    for (int i = 0; i <= (1 << 21); i++) {
        int bits = 0;
        long long cost = 0;
        for (int j = 1; j < n + 1; j++) {
            if (i & (1 << j)) {
                bits |= bm[j];
                cost += a[j];
            }
        }

        bool psb = true;
        for (int j = 1; j < n + 1; j++) { // 모든 정점 포함되는지 확인
            if (!(bits & (1 << j))) {
                psb = false;
                break;
            }
        }

        if (psb) ans = min(ans, cost);
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