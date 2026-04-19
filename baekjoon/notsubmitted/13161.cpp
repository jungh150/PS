// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/Ed-Karp.cpp

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAX = 510, INF = INT_MAX;
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

    int n;
    cin >> n;

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        if (x == 1) mf.makeEdge(508, i, INF);
        else if (x == 2) mf.makeEdge(i, 509, INF);
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int x;
            cin >> x;
            mf.makeEdge(i, j, x);
        }
    }

    cout << mf.solve(508, 509) << '\n';

    vector<int> vst(MAX, 0);
    queue<int> q;
    q.push(508);
    vst[508] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &e: mf.adj[u]) {
            if (!vst[e.next] && e.remain() > 0) {
                vst[e.next] = 1;
                q.push(e.next);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vst[i]) cout << i << ' ';
    }
    cout << '\n';

    for (int i = 1; i <= n; i++) {
        if (!vst[i]) cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}