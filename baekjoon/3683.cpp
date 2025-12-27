// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 501;
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

    int c, d, v;
    cin >> c >> d >> v;

    vector<int> a(v);
    vector<int> b(v);

    for (int i = 0; i < v; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        a[i] = stoi(s1.substr(1));
        if (s1[0] == 'D') a[i] += 100;
        b[i] = stoi(s2.substr(1));
        if (s2[0] == 'D') b[i] += 100;
    }

    for (int i = 0; i < v; i++) {
        for (int j = i + 1; j < v; j++) {
            if (a[i] == b[j] || a[j] == b[i]) {
                if (a[i] <= 100) bm.adj[i].push_back(j);
                else bm.adj[j].push_back(i);
            }
        }
    }

    cout << v - bm.biMatch() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}