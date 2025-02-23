#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> q(n);

    for (int i = 0; i < n; i++) cin >> q[i];

    vector<int> g(1000);
    for (int i = 0; i < 1000; i++) {
        g[i] = 3 * i * (i - 1) + 1;
    }

    sort(q.begin(), q.end());

    while (m--) {
        int u;
        cin >> u;

        auto ub = upper_bound(q.begin(), q.end(), u);
        int tmp = ub - q.begin();

        if (tmp == 0) cout << 0 << ' ';
        else cout << upper_bound(g.begin(), g.end(), tmp) - g.begin() - 1 << ' ';
    }
}