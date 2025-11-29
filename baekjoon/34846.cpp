#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> sw(n + 1, false);
    vector<int> cnt(n + 1, 0);

    while (q--) {
        int k, x;
        cin >> k >> x;

        if (k == 1) {
            if (sw[x]) continue;
            sw[x] = true;
            for (int nxt: adj[x]) cnt[nxt]++;
        } else if (k == 2) {
            cout << cnt[x] << '\n';
        }
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