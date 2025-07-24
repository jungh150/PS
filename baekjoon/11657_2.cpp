#include <iostream>
#include <vector>
using namespace std;

long long INTMAX = 1e12;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
    }

    vector<long long> dst(n + 1, INTMAX);
    dst[1] = 0;

    bool nc = false;
    for (int i = 0; i < n; i++) {
        for (int cur = 1; cur <= n; cur++) {
            if (dst[cur] == INTMAX) continue;
            for (auto [nxt, cost]: adj[cur]) {
                if (dst[cur] + cost < dst[nxt]) {
                    dst[nxt] = dst[cur] + cost;
                    if (i == n - 1) nc = true;
                }
            }
        }
    }

    if (nc) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 2; i < n + 1; i++) {
        if (dst[i] == INTMAX) cout << -1 << '\n';
        else cout << dst[i] << '\n';
    }
}