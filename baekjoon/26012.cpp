// Reference: green55 teamnote
// https://github.com/green5555/Teamnote/blob/master/TeamNote/BiMatch.cpp

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 750;
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
    int n;
    cin >> n;

    vector<int> odd;
    vector<int> even;
    bool chk = false;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            if (chk) continue;
            odd.push_back(x);
            chk = true;
        } else {
            if (x % 2 == 1) odd.push_back(x);
            else even.push_back(x);
        }
    }
    int oddsz = odd.size();
    int evensz = even.size();

    int num = 2 * 1e7 + 1;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    int sqnum = sqrt(num);
    for (int i = 2; i <= sqnum; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) p[j] = 0;
        }
    }

    BiMatching bm;
    
    for (int i = 0; i < oddsz; i++) {
        for (int j = 0; j < evensz; j++) {
            if (p[odd[i] + even[j]]) {
                bm.adj[i].push_back(j);
            }
        }
    }
    
    cout << evensz + oddsz - bm.biMatch() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}