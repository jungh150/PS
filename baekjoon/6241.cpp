// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/Ed-Karp.cpp

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAX = 500, INF = INT_MAX;
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

void solve() {
    maxflow mf;

    int n, f, d;
    cin >> n >> f >> d;

    for (int i = 1; i < n + 1; i++) {
        int fi, di;
        cin >> fi >> di;
        for (int j = 0; j < fi; j++) {
            int ff;
            cin >> ff;
            mf.makeEdge(ff, i + 100, 1);
        }
        for (int j = 0; j < di; j++) {
            int dd;
            cin >> dd;
            mf.makeEdge(i + 200, dd + 300, 1);
        }
        mf.makeEdge(i + 100, i + 200, 1);
    }

    for (int i = 1; i < f + 1; i++) mf.makeEdge(498, i, 1);
    for (int i = 1; i < d + 1; i++) mf.makeEdge(i + 300, 499, 1);

    cout << mf.solve(498, 499) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}