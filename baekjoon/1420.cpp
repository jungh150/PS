// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/Ed-Karp.cpp

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

const int MAX = 20210, INF = INT_MAX;
struct maxflow {
    struct edge {
        int next, cap, flow = 0, rev_idx;
        edge() {}
        edge(int n, int c) : next(n), cap(c) {}
        int remain() {
            return cap - flow;
        }
    };
    vector<edge> adj[MAX];
    void makeEdge(int u, int v, int c) {
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, 0);
        adj[u].back().rev_idx = adj[v].size() - 1;
        adj[v].back().rev_idx = adj[u].size() - 1;
    }
    int parent[MAX];
    pii path[MAX];
    int solve(int S, int E) {
        int ans = 0;
        queue<int> q;
        while (1) {
            memset(parent, -1, sizeof(parent));
            q.push(S);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < adj[u].size(); ++i) {
                    auto &e = adj[u][i];
                    if (e.remain() > 0 && parent[e.next] == -1) {
                        parent[e.next] = u;
                        path[e.next] = { u, i };
                        q.emplace(e.next);
                    }
                }
            }
            if (parent[E] == -1) break;
            int ret = INF;
            for (int i = E; i != S; i = parent[i])
                ret = min(ret, adj[path[i].first][path[i].second].remain());
            for (int i = E; i != S; i = parent[i]) {
                auto &e = adj[path[i].first][path[i].second];
                e.flow += ret;
                adj[e.next][e.rev_idx].flow -= ret;
            }
            ans += ret;
        }
        return ans;
    }
};

int conv(int i, int j) {return 2 * (100 * i + j);}

void solve() {
    maxflow mf;

    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int si, sj, ei, ej;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 정점 분할 (자신의 in -> 자신의 out)
            int tmp = conv(i, j);
            if (a[i][j] == 'K' || a[i][j] == 'H') { // 도현이나 학교이면
                mf.makeEdge(tmp, tmp + 1, INF); // 벽으로 바꿀 수 없으니까 가중치를 INF로
                if (a[i][j] == 'K') mf.makeEdge(20208, tmp, INF); // s -> 도현의 in
                else mf.makeEdge(tmp + 1, 20209, INF); // 학교의 out -> t
            } else if (a[i][j] == '.') { // 빈칸이면
                mf.makeEdge(tmp, tmp + 1, 1); // 정점 1개에 해당하니까 가중치를 1로
            } else { // 벽이면
                continue; // 다른 정점과 연결할 필요 X
            }
            // 다른 정점과 연결 (u의 in -> v의 out, u의 out -> v의 in)
            for (int k = 0; k < 4; k++) {
                int nxti = i + dx[k];
                int nxtj = j + dy[k];
                if (nxti < 0 || nxti >= n || nxtj < 0 || nxtj >= m || a[nxti][nxtj] == '#') continue;
                mf.makeEdge(tmp + 1, conv(nxti, nxtj), INF);
            }
        }
    }

    int ans = mf.solve(20208, 20209);
    if (ans == INF) cout << -1 << '\n';
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