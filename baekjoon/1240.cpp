#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        vector<bool> vst(n + 1, 0);
        queue<pair<int, int>> q;
        vst[a] = 1;
        q.emplace(a, 0);
        while (!q.empty()) {
            auto [cur, dst] = q.front();
            if (cur == b) {
                cout << dst << '\n';
                break;
            }
            q.pop();
            for (auto [nxt, d]: adj[cur]) {
                if (!vst[nxt]) {
                    vst[nxt] = 1;
                    q.emplace(nxt, dst + d);
                }
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