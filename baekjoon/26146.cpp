#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, m;
vector<vector<int>> adj1;
vector<vector<int>> adj2;
vector<bool> vst;
stack<int> st;

void dfs1(int cur) {
    vst[cur] = true;
    for (int nxt: adj1[cur]) {
        if (!vst[nxt]) dfs1(nxt);
    }
    st.push(cur);
}

void dfs2(int cur) {
    vst[cur] = true;
    for (int nxt: adj2[cur]) {
        if (!vst[nxt]) dfs2(nxt);
    }
}

void solve() {
    cin >> n >> m;
    adj1 = vector<vector<int>>(n + 1);
    adj2 = vector<vector<int>>(n + 1);
    for (int i = 0; i < m; i++) {
        int v, w;
        cin >> v >> w;
        adj1[v].push_back(w);
        adj2[w].push_back(v);
    }

    // first DFS
    vst = vector<bool>(n + 1, false);
    for (int i = 1; i < n + 1; i++) {
        if (!vst[i]) dfs1(i);
    }

    // second DFS
    int cnt = 0;
    vst = vector<bool>(n + 1, false);
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        if (!vst[x]) {
            dfs2(x);
            cnt++;
        }
    }

    if (cnt == 1) cout << "Yes\n";
    else cout << "No\n";
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