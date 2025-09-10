#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int v, e;
vector<vector<int>> adj1;
vector<vector<int>> adj2;
vector<bool> vst;
stack<int> stk;
vector<int> tmp;

void dfs1(int cur) {
    vst[cur] = true;
    for (int nxt: adj1[cur]) {
        if (!vst[nxt]) dfs1(nxt);
    }
    stk.push(cur);
}

void dfs2(int cur) {
    vst[cur] = true;
    tmp.push_back(cur);
    for (int nxt: adj2[cur]) {
        if (!vst[nxt]) dfs2(nxt);
    }
}

void solve() {
    cin >> v >> e;

    adj1 = vector<vector<int>>(v + 1);
    adj2 = vector<vector<int>>(v + 1);

    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adj1[a].push_back(b);
        adj2[b].push_back(a);
    }

    vst = vector<bool>(v + 1, false);
    for (int i = 1; i < v + 1; i++) {
        if (!vst[i]) dfs1(i);
    }

    vector<vector<int>> ans;
    vst = vector<bool>(v + 1, false);
    while (!stk.empty()) {
        int x = stk.top();
        stk.pop();
        if (!vst[x]) {
            tmp = vector<int>();
            dfs2(x);
            ans.push_back(tmp);
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        sort(ans[i].begin(), ans[i].end());
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        for (int x: ans[i]) cout << x << ' ';
        cout << "-1\n";
    }
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