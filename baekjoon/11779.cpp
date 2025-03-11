#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int MAX_SIZE = 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n + 1);
    vector<int> dst(n + 1, MAX_SIZE);
    vector<int> route(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }

    int s, e;
    cin >> s >> e;

    priority_queue<pair<int, int>> q;
    q.emplace(0, s);
    dst[s] = 0;

    while (!q.empty()) {
        int cost = -q.top().first;
        int cur = q.top().second;
        q.pop();

        if (cost > dst[cur]) continue; // 이거 왜 등호 있으면 메모리 초과일까????????

        for (auto nxt: g[cur]) {
            if (cost + nxt.second < dst[nxt.first]) {
                dst[nxt.first] = cost + nxt.second;
                q.emplace(-dst[nxt.first], nxt.first);
                route[nxt.first] = cur;
            }
        }
    }

    vector<int> ans;
    int idx = e;
    while (idx != s) {
        ans.push_back(idx);
        idx = route[idx];
    }
    ans.push_back(idx);

    cout << dst[e] << '\n' << ans.size() << '\n';
    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] << ' ';
    cout << '\n';
}