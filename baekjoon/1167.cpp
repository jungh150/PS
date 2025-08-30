#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
vector<vector<pair<int, int>>> adj;
vector<int> dst;

void bfs(int s) {
    vector<bool> vst(n + 1, 0);
    queue<int> q;
    q.push(s);
    vst[s] = 1;
    dst[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto [nxt, c]: adj[cur]) {
            if (!vst[nxt]) {
                q.push(nxt);
                vst[nxt] = 1;
                dst[nxt] = dst[cur] + c;
            }
        }
    }
}

void solve() {
    cin >> n;

    adj = vector<vector<pair<int, int>>>(n + 1);
    for (int i = 1; i < n + 1; i++) {
        int a, b, c;
        cin >> a;
        while (1) {
            cin >> b;
            if (b == -1) break;
            cin >> c;
            adj[a].emplace_back(b, c);
            adj[b].emplace_back(a, c);
        }
    }

    // dst[i] = 루트 정점에서 i번 정점까지의 거리
    dst = vector<int>(n + 1);
    bfs(1); // 임의의 정점에서 bfs 한 번 수행

    int maxi = 1;
    for (int i = 1; i < n + 1; i++) {
        if (dst[i] > dst[maxi]) maxi = i;
    }

    dst = vector<int>(n + 1);
    bfs(maxi); // 임의의 정점에서 가장 먼 노드에서 bfs 한 번 더 수행

    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        ans = max(ans, dst[i]);
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