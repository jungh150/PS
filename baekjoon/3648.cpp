#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, m, idx;
vector<vector<int>> adj1;
vector<vector<int>> adj2;
vector<bool> vst;
stack<int> stk;
vector<int> scc;

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

int neg(int x) {
    if (x <= n) return x + n;
    else return x - n;
}

void solve() {
    adj1 = vector<vector<int>>(2 * n + 1);
    adj2 = vector<vector<int>>(2 * n + 1);

    // 상근이는 무조건 진출: ~x1 -> x1
    adj1[neg(1)].push_back(1);
    adj2[1].push_back(neg(1));

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        if (a < 0) a = -a + n;
        if (b < 0) b = -b + n;

        adj1[neg(a)].push_back(b);
        adj1[neg(b)].push_back(a);
        adj2[b].push_back(neg(a));
        adj2[a].push_back(neg(b));
    }

    vst = vector<bool>(2 * n + 1, false);
    for (int i = 1; i < 2 * n + 1; i++) {
        if (!vst[i]) dfs1(i);
    }

    idx = 0;
    scc = vector<int>(2 * n + 1, -1);
    vst = vector<bool>(2 * n + 1, false);
    while (!stk.empty()) {
        int x = stk.top();
        stk.pop();
        if (!vst[x]) {
            dfs2(x);
            idx++;
        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (scc[i] == scc[neg(i)]) {
            cout << "no\n";
            return;
        }
    }

    cout << "yes\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> n >> m) {
        solve();
    }
}