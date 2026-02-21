#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> ans(n, vector<char>(m, '.'));

    if (n < 3 || m < 3 || n % 2 != m % 2) {
        cout << -1 << '\n';
        return;
    }

    ans[n - 2][0] = 'G';
    ans[n - 1][0] = 'g';
    ans[n - 1][1] = 'G';
    ans[n - 1][2] = 'g';
    ans[n - 3][2] = 'G';
    ans[n - 2][2] = 'g';

    int i = n - 4;
    int j = 3;
    for (; i >= 0; i--) {
        if (j >= m) break;
        ans[i][j] = 'G';
        ans[i + 1][j] = 'g';
        j++;
    }

    if (n > m) {
        for (; i >= 0; i--) {
            ans[i][0] = 'G';
            ans[i][1] = 'g';
        }
    } else if (n < m) {
        for (; j < m; j++) {
            ans[0][j] = 'G';
            ans[1][j] = 'g';
        }
    }

    cout << max(n, m) << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
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