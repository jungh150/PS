// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/dinic.cpp

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 401, INF = INT_MAX;
struct Dinic {
    struct edg {int pos, cap, rev;};
    vector<edg> adj[MAX];
    void clear() { for (int i = 0; i < MAX; i++) adj[i].clear(); }
    void make_edge(int s, int e, int x) {
        adj[s].push_back({e, x, (int) adj[e].size()});
        adj[e].push_back({s, 0, (int) adj[s].size() - 1});
    }
    int dis[MAX], pnt[MAX];
    bool bfs(int src, int sink) {
        memset(dis, 0, sizeof(dis));
        memset(pnt, 0, sizeof(pnt));
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (auto &e : adj[x]) {
                if (e.cap > 0 && !dis[e.pos]) {
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }
    int dfs(int x, int sink, int f) {
        if (x == sink) return f;
        for (; pnt[x] < adj[x].size(); pnt[x]++) {
            edg e = adj[x][pnt[x]];
            if (e.cap > 0 && dis[e.pos] == dis[x] + 1) {
                int w = dfs(e.pos, sink, min(f, e.cap));
                if (w) {
                    adj[x][pnt[x]].cap -= w;
                    adj[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }
    ll maxflow(int src, int sink) {
        ll ret = 0;
        while (bfs(src, sink)) {
            int r;
            while ((r = dfs(src, sink, 2e9))) ret += r;
        }
        return ret;
    }
};

void solve() {
    Dinic mf;

    int n, m;
    cin >> n >> m;

    int s, e;
    cin >> s >> e;

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        mf.make_edge(i, i + 200, x);
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        mf.make_edge(a + 200, b, INF);
        mf.make_edge(b + 200, a, INF);
    }

    mf.maxflow(s, e + 200);

    vector<int> vst(MAX, 0);
    queue<int> q;
    q.push(s);
    vst[s] = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &ed: mf.adj[u]) {
            if (!vst[ed.pos] && ed.cap > 0) {
                vst[ed.pos] = 1;
                q.push(ed.pos);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vst[i] && !vst[i + 200]) {
            cout << i << ' ';
        }
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