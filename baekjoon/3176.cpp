#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, k;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> parent;
vector<vector<int>> minc;
vector<vector<int>> maxc;
vector<int> depth;

void bfs(int s) {
    vector<bool> vst(n + 1, false);
    queue<int> q;
    q.push(s);
    vst[s] = true;
    parent[s][0] = 0;
    depth[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto [nxt, c]: adj[cur]) {
            if (!vst[nxt]) {
                q.push(nxt);
                vst[nxt] = true;
                parent[nxt][0] = cur;
                minc[nxt][0] = c;
                maxc[nxt][0] = c;
                depth[nxt] = depth[cur] + 1;
            }
        }
    }
}

pair<int, int> lca(int a, int b) {
    int mina = 1e7;
    int maxa = 0;

    if (depth[a] > depth[b]) swap(a, b); // now, depth[a] < depth[b]

    // a와 b의 depth 차이만큼 끌어올리기
    int diff = depth[b] - depth[a];
    for (int k = 0; k < 20; k++) {
        if (diff & (1 << k)) {
            mina = min(mina, minc[b][k]);
            maxa = max(maxa, maxc[b][k]);
            b = parent[b][k];
        }
    }
    if (a == b) return {mina, maxa}; // 둘이 같다면 그것이 lca

    // a와 b 모두 2^k만큼 끌어올려보고 같으면 끌어올리지 말기 (k = 19부터 k = 0까지 반복)
    for (int k = 19; k >= 0; k--) {
        if (parent[a][k] != parent[b][k]) {
            mina = min(mina, min(minc[a][k], minc[b][k]));
            maxa = max(maxa, max(maxc[a][k], maxc[b][k]));
            a = parent[a][k];
            b = parent[b][k];
        }
    }
    mina = min(mina, min(minc[a][0], minc[b][0]));
    maxa = max(maxa, max(maxc[a][0], maxc[b][0]));

    return {mina, maxa}; // 그 후 둘의 부모가 lca
}

void solve() {
    cin >> n;
    adj = vector<vector<pair<int, int>>>(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    // parent[i][j] = i번 정점의 2^j번째 부모 노드
    parent = vector<vector<int>>(n + 1, vector<int>(20, 0));
    // minc[i][j] = i번 정점부터 2^j번째 부모 노드까지의 가장 짧은 도로의 길이
    minc = vector<vector<int>>(n + 1, vector<int>(20, 1e7));
    // maxc[i][j] = i번 정점부터 2^j번째 부모 노드까지의  가장 긴 도로의 길이
    maxc = vector<vector<int>>(n + 1, vector<int>(20, 0));
    // depth[i] = i번 정점의 깊이
    depth = vector<int>(n + 1);

    bfs(1);

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < n + 1; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            minc[i][j] = min(minc[i][j - 1], minc[parent[i][j - 1]][j - 1]);
            maxc[i][j] = max(maxc[i][j - 1], maxc[parent[i][j - 1]][j - 1]);
        }
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        int d, e;
        cin >> d >> e;
        auto [x, y] = lca(d, e);
        cout << x << ' ' << y << '\n';
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