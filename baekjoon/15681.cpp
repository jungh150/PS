#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> g;
vector<vector<int>> t;
vector<int> cnt;
queue<pair<int, int>> que;
queue<int> que2;

int subtree(int root) {
    if (t[root].size() == 0) {
        cnt[root] = 1;
        return 1;
    } else {
        if (cnt[root] != -1) {
            return cnt[root];
        }
        int rt = 1;
        for (int x: t[root]) {
            rt += subtree(x);
        }
        cnt[root] = rt;
        return rt;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, r, q;
    cin >> n >> r >> q;

    g = vector<vector<int>>(n + 1, vector<int>());
    t = vector<vector<int>>(n + 1, vector<int>());
    cnt = vector<int>(n + 1, -1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    que.emplace(-1, r);
    while (!que.empty()) {
        int pre = que.front().first;
        int cur = que.front().second;
        que.pop();
        for (int nxt: g[cur]) {
            if (nxt != pre) {
                t[cur].push_back(nxt);
                que.emplace(cur, nxt);
            }
        }
    }

    while(q--) {
        int s;
        cin >> s;
        cout << subtree(s) << '\n';
    }
}