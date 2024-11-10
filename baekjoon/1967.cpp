#include <iostream>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> g;
vector<bool> vst;
int maxc = 0;

void dfs(int cur, int cnt) {
    vst[cur] = true;
    if (cnt > maxc) maxc = cnt;
    for (auto nxt: g[cur]) {
        if (!vst[nxt.first]) dfs(nxt.first, cnt + nxt.second);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    g = vector<vector<pair<int, int>>>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    for (int i = 1; i < n + 1; i++) {
        vst = vector<bool>(n + 1, false);
        dfs(i, 0);
    }

    cout << maxc << '\n';
}