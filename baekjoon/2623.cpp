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
    queue<int> q;
    vector<int> ans;

    while (m--) {
        int x;
        cin >> x;
        int pre, cur;
        cin >> pre;
        while (--x) {
            cin >> cur;
            g[pre].push_back(cur);
            indegree[cur]++;
            pre = cur;

        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ans.push_back(cur);

        for (int nxt: g[cur]) {
            indegree[nxt]--;
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }

    if (ans.size() != n) {
        cout << "0\n";
    } else {
        for (int x : ans) cout << x << '\n';
    }
}