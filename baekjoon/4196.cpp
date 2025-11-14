#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> adj1;
vector<vector<int>> adj2;
vector<bool> vst;
stack<int> stk;
vector<int> scc;
int idx;

void dfs1(int cur) {
    vst[cur] = true;
    for (int nxt: adj1[cur]) {
        if (!vst[nxt]) dfs1(nxt);
    }
    stk.push(cur);
}

void dfs2(int cur) {
    vst[cur] = true;
    scc[cur] = idx;
    for (int nxt: adj2[cur]) {
        if (!vst[nxt]) dfs2(nxt);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    adj1 = vector<vector<int>>(n + 1);
    adj2 = vector<vector<int>>(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj1[x].push_back(y);
        adj2[y].push_back(x);
    }

    vst = vector<bool>(n + 1, false);
    for (int i = 1; i < n + 1; i++) {
        if (!vst[i]) dfs1(i);
    }

    vst = vector<bool>(n + 1, false);
    scc = vector<int>(n + 1, -1);
    idx = 0;
    while (!stk.empty()) {
        int x = stk.top();
        stk.pop();
        if (!vst[x]) {
            dfs2(x);
            idx++;
        }
    }

    vector<int> sccin(idx, 0);
    for (int cur = 1; cur < n + 1; cur++) {
        for (int nxt: adj1[cur]) {
            if (scc[cur] != scc[nxt]) {
                sccin[scc[nxt]]++;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < idx; i++) {
        if (sccin[i] == 0) ans++;
    }
    cout << ans << '\n';
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