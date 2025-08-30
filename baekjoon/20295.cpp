#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> store;
vector<vector<int>> adj;
vector<vector<int>> parent;
vector<int> depth;
vector<vector<int>> candy;

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

// lcacandy: a -> lca -> b 이동 시에 얻을 수 있는 사탕 (비트마스킹) 반환
int lcacandy(int a, int b) {
    int res = 0;

    if (depth[a] > depth[b]) swap(a, b); // now, depth[a] < depth[b]

    // a와 b의 depth 차이만큼 끌어올리기
    int diff = depth[b] - depth[a];
    for (int k = 0; k < 20; k++) {
        if (diff & (1 << k)) {
            res |= candy[b][k];
            b = parent[b][k];
        }
    }
    if (a == b) {
        res |= (1 << store[a]);
        return res;
    }

    // a와 b 모두 2^k만큼 끌어올려보고 같으면 끌어올리지 말기 (k = 19부터 k = 0까지 반복)
    for (int k = 19; k >= 0; k--) {
        if (parent[a][k] != parent[b][k]) {
            res |= candy[a][k];
            a = parent[a][k];
            res |= candy[b][k];
            b = parent[b][k];
        }
    }
    res |= candy[a][0];
    res |= candy[b][0];
    res |= (1 << (store[parent[a][0]]));
    return res;
}

void solve() {
    cin >> n;

    store = vector<int>(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> store[i];

    adj = vector<vector<int>>(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // parent[i][j] = i번 정점의 2^j번째 부모 노드
    parent = vector<vector<int>>(n + 1, vector<int>(20, 0));
    // depth[i] = i번 정점의 깊이
    depth = vector<int>(n + 1);
    // candy[i][j] = i번 정점에서 2^j번째 부모 노드 직전까지 이동할 때 얻을 수 있는 사탕 (비트마스킹)
    candy = vector<vector<int>>(n + 1, vector<int>(20, 0));

    for (int i = 1; i < n + 1; i++) candy[i][0] = (1 << store[i]);

    bfs(1);

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < n + 1; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            candy[i][j] = (candy[i][j - 1] | candy[parent[i][j - 1]][j - 1]);
        }
    }

    cin >> m;
    int cur, nxt, k;

    // 출발 정점은 선택 가능
    cin >> nxt >> k;
    bool psb = false;
    for (int i = 1; i < n + 1; i++) {
        if (lcacandy(i, nxt) & (1 << k)) {
            psb = true;
            break;
        }
    }
    if (psb) cout << "PLAY\n";
    else cout << "CRY\n";
    cur = nxt;

    // (m - 1)번 반복
    for (int i = 0; i < m - 1; i++) {
        cin >> nxt >> k;
        if (lcacandy(cur, nxt) & (1 << k)) cout << "PLAY\n";
        else cout << "CRY\n";
        cur = nxt;
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