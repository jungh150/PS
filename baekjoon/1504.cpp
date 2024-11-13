#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int INTMAX = 10000000;
int n, e, v1, v2;
vector<vector<pair<int, int>>> edge;

int dijkstra(int s, int e) {
    vector<int> dst(n + 1, INTMAX);
    priority_queue<pair<int, int>> pq;

    dst[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        for (auto nxt: edge[cur]) {
            int newcost = cost + nxt.second;
            if (newcost < dst[nxt.first]) {
                dst[nxt.first] = newcost;
                pq.emplace(-newcost, nxt.first);
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
    edge = vector<vector<pair<int, int>>>(n + 1);

    for (int i = 0; i < e; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[a].emplace_back(b, c);
        edge[b].emplace_back(a, c);
    }

    cin >> v1 >> v2;

    int ans1 = dijkstra(1, v1) + dijkstra(v1, v2) + dijkstra(v2, n);
    int ans2 = dijkstra(1, v2) + dijkstra(v2, v1) + dijkstra(v1, n);
    if (ans1 >= INTMAX && ans2 >= INTMAX) cout << -1 << '\n';
    else cout << min(ans1, ans2) << '\n';
}