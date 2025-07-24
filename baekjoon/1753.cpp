#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INTMAX = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int v, e, s;
    cin >> v >> e >> s;

    vector<vector<pair<int, int>>> adj(v + 1);

    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
    }

    vector<int> dst(v + 1, INTMAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

    dst[s] = 0;
    q.emplace(dst[s], s);
    
    while (!q.empty()) {
        auto [curd, cur] = q.top();
        q.pop();
        for (auto [nxt, w]: adj[cur]) {
            int newdst = curd + w;
            if (newdst < dst[nxt]) {
                dst[nxt] = newdst;
                q.emplace(newdst, nxt);
            }
        }
    }

    for (int i = 1; i < v + 1; i++) {
        if (dst[i] == INTMAX) cout << "INF\n";
        else cout << dst[i] << '\n';
    }
}