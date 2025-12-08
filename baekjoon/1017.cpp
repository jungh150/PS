// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2001;
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
    int num = 2001;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i * i < num; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) {
                p[j] = 0;
            }
        }
    }

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> ans;
    for (int i = 1; i < n; i++) {
        if (p[a[0] + a[i]]) {
            BiMatching bm;
            for (int j = 1; j < n; j++) {
                if (j == i || a[j] % 2 == 0) continue;
                for (int k = 1; k < n; k++) {
                    if (k == i || a[k] % 2 == 1) continue;
                    if (p[a[j] + a[k]]) {
                        bm.adj[j].push_back(k);
                    }
                }
            }
            if (bm.biMatch() == (n / 2 - 1)) {
                ans.push_back(a[i]);
            }
        }
    }

    sort(ans.begin(), ans.end());

    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}