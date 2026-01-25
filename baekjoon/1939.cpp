#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    int s, e;
    cin >> s >> e;

    int l = 0;
    int r = 1e9 + 1;
    while (l < r) {
        int m = (l + r) / 2;
        bool psb = true;

        vector<bool> vst(n + 1, 0);
        queue<int> q;
        vst[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto [nxt, c]: adj[cur]) {
                cout << nxt;
            }
        }
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