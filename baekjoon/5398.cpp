// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
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

    vector<pair<int, int>> pos1(n);
    vector<string> word1(n);
    for (int i = 0; i < n; i++) cin >> pos1[i].first >> pos1[i].second >> word1[i];
    
    vector<pair<int, int>> pos2(m);
    vector<string> word2(m);
    for (int i = 0; i < m; i++) cin >> pos2[i].first >> pos2[i].second >> word2[i];

    for (int i = 0; i < n; i++) {
        // 가로
        int x1 = pos1[i].first;
        int y1 = pos1[i].second;
        int l1 = word1[i].size();
        for (int j = 0; j < m; j++) {
            // 세로
            int x2 = pos2[j].first;
            int y2 = pos2[j].second;
            int l2 = word2[j].size();
            // 교차점: (x2, y1)
            if (x1 <= x2 && x2 < x1 + l1 && y2 <= y1 && y1 < y2 + l2) {
                if (word1[i][x2 - x1] != word2[j][y1 - y2]) {
                    bm.adj[i].push_back(j);
                }
            }
        }
    }

    cout << n + m - bm.biMatch() << '\n';
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