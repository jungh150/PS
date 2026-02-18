#include <iostream>
#include <vector>
#include <set>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> color(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        set<int> s;
        for (int nxt: adj[i]) {
            if (color[nxt] != 0) s.insert(color[nxt]);
        }

        for (int j = 1; j < n + 1; j++) {
            if (!s.count(j)) {
                color[i] = j;
                break;
            }
        }
    }

    for (int i = 1; i < n + 1; i++) cout << color[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}