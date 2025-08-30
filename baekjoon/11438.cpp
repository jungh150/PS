#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> parent;
vector<int> depth;

void bfs(int s) {
    vector<bool> vst(n + 1, 0);
    queue<int> q;
    q.push(s);
    vst[s] = 1;
    parent[s][0] = 0;
    depth[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt: adj[cur]) {
            if (!vst[nxt]) {
                q.push(nxt);
                vst[nxt] = 1;
                parent[nxt][0] = cur;
                depth[nxt] = depth[cur] + 1;
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b); // now, depth[a] < depth[b]

    // a와 b의 depth 차이만큼 끌어올리기
    int diff = depth[b] - depth[a];
    for (int k = 0; k < 20; k++) {
        if (diff & (1 << k)) b = parent[b][k];
    }
    if (a == b) return a; // 둘이 같다면 그것이 lca

    // a와 b 모두 2^k만큼 끌어올려보고 같으면 끌어올리지 말기 (k = 19부터 k = 0까지 반복)
    for (int k = 19; k >= 0; k--) {
        if (parent[a][k] != parent[b][k]) {
            a = parent[a][k];
            b = parent[b][k];
        }
    }
    return parent[a][0]; // 그 후 둘의 부모가 lca
}

void solve() {
    cin >> n;

    adj = vector<vector<int>>(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // parent[i][j] = i번 정점의 2^j번째 부모 노드
    parent = vector<vector<int>>(n + 1, vector<int>(20, 0));
    // depth[i] = i번 정점의 깊이
    depth = vector<int>(n + 1);

    bfs(1);

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < n + 1; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }

    cin >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << '\n';
    }
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