#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k, w;
        cin >> n >> k;

        vector<vector<int>> g(n + 1);
        vector<int> time(n + 1);
        vector<int> totaltime(n + 1);
        vector<int> indegree(n + 1, 0);
        queue<int> q;

        for (int i = 1; i < n + 1; i++) cin >> time[i];

        while (k--) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            indegree[b]++;
        }

        cin >> w;

        for (int i = 1; i < n + 1; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                totaltime[i] = time[i];
            }
        }

        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int nxt: g[cur]) {
                indegree[nxt]--;
                if (indegree[nxt] == 0) q.push(nxt);
                totaltime[nxt] = max(totaltime[nxt], totaltime[cur] + time[nxt]);
            }
        }

        cout << totaltime[w] << '\n';
    }
}