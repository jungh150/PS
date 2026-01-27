// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 151;
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

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (a[i] == a[j] && b[i] == b[j] && c[i] == c[j]) {
                if (i < j) {
                    bm.adj[i].push_back(j + 100);
                    bm.adj[i + 50].push_back(j + 100);
                }
            } else if (a[i] >= a[j] && b[i] >= b[j] && c[i] >= c[j]) {
                bm.adj[i].push_back(j + 100);
                bm.adj[i + 50].push_back(j + 100);
            }
        }
    }

    cout << n - bm.biMatch() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}