#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;

    // 세로로 보면서 체크 (오: 1 / 왼: 2)
    for (int j = 0; j < m - 1; j++) {
        int pre = 0;
        int cur = 0;
        int cnt = 1;
        for (int i = 0; i < n; i++) {
            if (a[i][j] == 'X' && a[i][j + 1] == '.') cur = 1;
            else if (a[i][j] == '.' && a[i][j + 1] == 'X') cur = 2;
            else cur = 0;

            if (cur != 0 && cur == pre) {
                cnt++;
            } else {
                ans += (cnt / 2);
                cnt = 1;
            }
            pre = cur;
        }
    }

    // 가로로 보면서 체크 (1: 아래 / 2: 위)
    for (int i = 0; i < n - 1; i++) {
        int pre = 0;
        int cur = 0;
        int cnt = 1;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'X' && a[i + 1][j] == '.') cur = 1;
            else if (a[i][j] == '.' && a[i + 1][j] == 'X') cur = 2;
            else cur = 0;

            if (cur != 0 && cur == pre) {
                cnt++;
            } else {
                ans += (cnt / 2);
                cnt = 1;
            }
            pre = cur;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}