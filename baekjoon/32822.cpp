#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> diff(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> diff[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            diff[i][j] = abs(diff[i][j] - x);
        }
    }

    vector<int> maxt(n, 0); // 해당 열의 최대
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            maxt[j] = max(maxt[j], diff[i][j]);
        }
    }

    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    long long ans = 0;
    for (int i = 0; i < m; i++) ans += maxt[b[i] - 1];

    cout << ans << '\n';
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