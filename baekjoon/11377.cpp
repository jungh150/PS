// 출처: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/Ed-Karp.cpp

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int n, m, k;

const int MAX = 2010, INF = INT_MAX;
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

    cin >> n >> m >> k;

    mf.makeEdge(2008, 2007, k); // s -> 중간 노드
    for (int i = 1; i < n + 1; i++) {
        int cnt;
        cin >> cnt;
        mf.makeEdge(2008, i, 1); // s -> 직원
        mf.makeEdge(2007, i, 1); // 중간 노드 -> 직원
        while (cnt--) {
            int j;
            cin >> j;
            mf.makeEdge(i, j + 1000, 1);
        }
    }

    for (int j = 1; j < m + 1; j++) {
        mf.makeEdge(j + 1000, 2009, 1); // 일 -> t
    }

    cout << mf.solve(2008, 2009) << '\n';
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