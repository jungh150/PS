#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<bool> visited;
vector<vector<int>> g;
int n;

int bfs(int start) {
    queue<int> q;
    int cnt = 0;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt: g[cur]) {
            if (!visited[nxt]) {
                q.push(nxt);
                visited[nxt] = true;
                cnt++;
            }
        }
    }

    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    visited = vector<bool>(n + 1, false);
    g = vector<vector<int>>(n + 1, vector<int>());

    int e, a, b;
    cin >> e;
    
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int cnt = bfs(1);

    cout << cnt << '\n';
}