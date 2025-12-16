#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dx[] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {0, -1, 0, 1, -1, 1, -1, 0, 1};

void solve() {
    int n = 8;
    vector<string> a(n);
    for (int i = n - 1; i >= 0; i--) cin >> a[i];

    vector<vector<bool>> pre, cur;
    pre = vector<vector<bool>>(n, vector<bool>(n, false));
    pre[0][0] = 1;
    for (int t = 0; t < 20; t++) {
        cur = vector<vector<bool>>(n, vector<bool>(n, false));
        // 욱제 이동
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!pre[i][j]) continue;
                for (int k = 0; k < 9; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= n || a[ni][nj] == '#') continue;
                    cur[ni][nj] = 1;
                }
            }
        }
        // 벽 이동
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i - 1][j] = a[i][j];
            }
        }
        for (int j = 0; j < n; j++) a[n - 1][j] = '.';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == '#') cur[i][j] = 0;
            }
        }
        swap(pre, cur);
    }

    if (pre[n - 1][n - 1]) cout << 1 << '\n';
    else cout << 0 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}