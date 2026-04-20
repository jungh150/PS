// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 401;
struct BiMatching {
    vector<int> adj[MAX+5];
    int iter, A[MAX+5], B[MAX+5], was[MAX+5];

    bool dfs(int u) {
        was[u] = iter;
        for (int v : adj[u]) {
            if (B[v] == -1) {
                A[u] = v;
                B[v] = u;
                return true;
            }
        }
        for (int v : adj[u]) {
            if (was[B[v]] != iter && dfs(B[v])) {
                A[u] = v;
                B[v] = u;
                return true;
            }
        }
        return false;
    }

    int biMatch(int n=MAX) {
        fill(A, A+n, -1);
        fill(B, B+n, -1);
        fill(was, was+n, 0);
        iter = 0;
        int res = 0;
        while (true) {
            iter++;
            int add = 0;
            for (int i = 0; i < n; i++) {
                if (A[i] == -1 && dfs(i)) {
                    add++;
                }
            }
            if (add == 0) {
                break;
            }
            res += add;
        }
        return res;
    }
};

void solve() {
    BiMatching bm;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> diff(n + 1, vector<int>(n + 1, 0)); // 차분배열

    auto ban = [&](int val, int l, int r) {
        if (l > r) return;
        diff[val][l] += 1;
        if (r + 1 <= n) diff[val][r + 1] -= 1;
    };

    while (m--) {
        int op, x, y, v;
        cin >> op >> x >> y >> v;
        if (op == 1) {
            // v는 [1, x - 1] 금지 [y + 1, n] 금지
            ban(v, 1, x - 1);
            ban(v, y + 1, n);
            // (v + 1) ~ n은 [x, y] 금지
            for (int i = v + 1; i < n + 1; i++) ban(i, x, y);
        } else {
            // v는 [1, x - 1] 금지 [y + 1, n] 금지
            ban(v, 1, x - 1);
            ban(v, y + 1, n);
            // 1 ~ (v - 1)은 [x, y] 금지
            for (int i = 1; i <= v - 1; i++) ban(i, x, y);
        }
    }

    for (int i = 1; i < n + 1; i++) {
        int tmp = 0;
        for (int j = 1; j < n + 1; j++) {
            tmp += diff[i][j];
            if (tmp == 0) bm.adj[i].push_back(j);
        }
    }

    if (bm.biMatch() != n) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 1; i < n + 1; i++) cout << bm.B[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}