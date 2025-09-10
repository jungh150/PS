#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> adj;
vector<vector<int>> dp;

int td(int pre, int cur, int st) {
    if (dp[cur][st] != -1) return dp[cur][st];

    dp[cur][st] = st;
    if (st == 0) { // not early adaptor
        for (int nxt: adj[cur]) {
            if (nxt == pre) continue;
            dp[cur][st] += td(cur, nxt, 1);
        }
    } else if (st == 1) { // early adaptor
        for (int nxt: adj[cur]) {
            if (nxt == pre) continue;
            dp[cur][st] += min(td(cur, nxt, 0), td(cur, nxt, 1));
        }
    }

    return dp[cur][st];
}

void solve() {
    cin >> n;

    adj = vector<vector<int>>(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // dp[i][j]: i번 노드가 j 상태일 때, i번 노드를 루트로 하는 서브트리에서 필요한 early adaptor 최소 개수
    dp = vector<vector<int>>(n + 1, vector<int>(2, -1));
    
    cout << min(td(-1, 1, 0), td(-1, 1, 1)) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}