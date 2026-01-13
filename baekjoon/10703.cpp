#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int mincnt = 10000;
    for (int j = 0; j < m; j++) {
        int cnt = 10000;
        for (int i = 0; i < n; i++) {
            if (a[i][j] == 'X') cnt = 0;
            else if (a[i][j] == '.') cnt++;
            else if (a[i][j] == '#') break;
        }
        mincnt = min(mincnt, cnt);
    }

    if (mincnt == 10000) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << '.';
            cout << '\n';
        }
    }

    vector<vector<char>> ans(n, vector<char>(m, '.'));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'X') ans[i + mincnt][j] = 'X';
            else if (a[i][j] == '#') ans[i][j] = '#';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << ans[i][j];
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