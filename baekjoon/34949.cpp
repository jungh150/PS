#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<vector<int>> b(n + 1);
    vector<int> vst(n + 1, -1);

    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        b[a[i]].push_back(i);
    }

    queue<int> q;
    q.push(n);
    vst[n] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int nxt: b[cur]) {
            if (vst[nxt] == -1) {
                q.push(nxt);
                vst[nxt] = vst[cur] + 1;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        cout << vst[i];
        if (i < n) cout << '\n';
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