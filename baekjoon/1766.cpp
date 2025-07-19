#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    vector<int> indegree(n + 1, 0);
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans;

    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        indegree[b]++;
    }

    for (int i = 1; i < n + 1; i++) {
        if (indegree[i] == 0) pq.push(i);
    }

    while (!pq.empty()) {
        int cur = pq.top();
        pq.pop();
        ans.push_back(cur);

        for (int nxt: g[cur]) {
            indegree[nxt]--;
            if (indegree[nxt] == 0) pq.push(nxt);
        }
    }

    for (int x : ans) cout << x << ' ';
    cout << '\n';
}