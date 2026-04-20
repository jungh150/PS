// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 10000;
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

    vector<vector<int>> diag1(n + 1, vector<int>(n + 1));
    vector<vector<int>> diag2(n + 1, vector<int>(n + 1));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        diag1[a][b] = -1;
        diag2[a][b] = -1;
    }

    // \ direction
    int idx = 0;
    for (int j = 1; j < n + 1; j++) {
        // start from (1, j)
        idx++;
        for (int k = 0; 1 + k < n + 1 && j + k < n + 1; k++) {
            if (diag1[1 + k][j + k] == -1) idx++;
            else diag1[1 + k][j + k] = idx;
        }
    }
    for (int i = 2; i < n + 1; i++) {
        // start from (i, 1)
        idx++;
        for (int k = 0; i + k < n + 1 && 1 + k < n + 1; k++) {
            if (diag1[i + k][1 + k] == -1) idx++;
            else diag1[i + k][1 + k] = idx;
        }
    }

    // / direction
    for (int j = 1; j < n + 1; j++) {
        // start from (1, j)
        idx++;
        for (int k = 0; 1 + k < n + 1 && j - k >= 1; k++) {
            if (diag2[1 + k][j - k] == -1) idx++;
            else diag2[1 + k][j - k] = idx;
        }
    }
    for (int i = 2; i < n + 1; i++) {
        // start from (i, n)
        idx++;
        for (int k = 0; i + k < n + 1 && n - k >= 1; k++) {
            if (diag2[i + k][n - k] == -1) idx++;
            else diag2[i + k][n - k] = idx;
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (diag1[i][j] == -1) continue;
            bm.adj[diag1[i][j]].push_back(diag2[i][j]);
        }
    }

    cout << bm.biMatch(idx + 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}