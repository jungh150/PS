// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

int n, m;

int dx[] = {-1, -1, 0, 0, 1, 1};
int dy[] = {-1, 1, -1, 1, -1, 1};

const int MAX = 7000;
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

int conv(int i, int j) {return (80 * i + j);}

void solve() {
    BiMatching bm;

    cin >> n >> m;
    vector<vector<bool>> a(n, vector<bool>(m, false));

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            a[i][j] = (c == '.');
            if (a[i][j]) ans++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j += 2) {
            if (!a[i][j]) continue;
            for (int k = 0; k < 6; k++) {
                int nxti = i + dx[k];
                int nxtj = j + dy[k];
                if (nxti < 0 || nxti >= n || nxtj < 0 || nxtj >= m || !a[nxti][nxtj]) continue;
                bm.adj[conv(i, j)].push_back(conv(nxti, nxtj));
            }
        }
    }

    cout << ans - bm.biMatch() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}