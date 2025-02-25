#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<bool> vst;
vector<vector<int>> g;

void dfs(int cur) {
    vst[cur] = true;
    cout << cur << ' ';
    for (int nxt: g[cur]) {
        if (!vst[nxt]) dfs(nxt);
    }
}

void bfs(int cur) {
    queue<int> q;
    q.push(cur);
    vst[cur] = true;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        cout << cur << ' ';
        for (int nxt: g[cur]) {
            if (!vst[nxt]) {
                q.push(nxt);
                vst[nxt] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, v;
    cin >> n >> m >> v;

    vst = vector<bool>(n + 1, false);
    g = vector<vector<int>>(n + 1);

    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // 작은 정점부터 방문하기 위해 정렬
    for (int i = 0; i < n + 1; i++) sort(g[i].begin(), g[i].end());

    dfs(v);
    cout << '\n';

    // 방문 여부 배열 초기화
    fill(vst.begin(), vst.end(), false);

    bfs(v);
    cout << '\n';
}