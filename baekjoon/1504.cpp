#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INTMAX = 1e9;
int n, e;
vector<vector<pair<int, int>>> adj;

long long dij(int s, int e) {
    vector<int> dst(n + 1, INTMAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

    dst[s] = 0;
    q.emplace(dst[s], s);

    while (!q.empty()) {
        auto [curd, cur] = q.top();
        q.pop();
        for (auto [nxt, cost]: adj[cur]) {
            int newcost = curd + cost;
            if (newcost < dst[nxt]) {
                dst[nxt] = newcost;
                q.emplace(dst[nxt], nxt);
            }
        }
    }

    return dst[e];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> e;
    adj = vector<vector<pair<int, int>>>(n + 1);

    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    int v1, v2;
    cin >> v1 >> v2;

    long long ans1 = dij(1, v1) + dij(v1, v2) + dij(v2, n);
    long long ans2 = dij(1, v2) + dij(v2, v1) + dij(v1, n);
    if (ans1 >= INTMAX && ans2 >= INTMAX) cout << -1 << '\n';
    else cout << min(ans1, ans2) << '\n';
}