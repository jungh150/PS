#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(2));
    for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];

    while (m--) {
        int g, x, y;
        cin >> g >> x >> y;
        int rest = g - x - y;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int xneed = a[i][0] - x;
            int yneed = a[i][1] - y;
            if ((a[i][0] + a[i][1] <= g) && (xneed >= 0) && (yneed >= 0)) ans++;
        }
        cout << ans << '\n';
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