#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int mod = 998244353;
int n, m, ansp, ansq;
vector<vector<vector<int>>> g;

void dfs(int idx, int curp, int curq) {
    if (idx == m + 1) {
        // update
        return;
    } else if (idx > m + 1) {
        return;
    }
    for (vector<int> nxt: g[idx]) {
        int nxtidx = nxt[0];
        int nxtp = nxt[1];
        int nxtq = nxt[2];
        // dfs(nxt[0], curp * nxt[1], curq * nxt[1])
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    g = vector<vector<vector<int>>>(m + 1);

    for (int i = 0; i < n; i++) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        g[l].emplace_back(r, p, q);
    }
}