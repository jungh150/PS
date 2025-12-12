#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void solve() {
    int r, c, n;
    cin >> r >> c >> n;

    vector<vector<int>> a(r, vector<int>(c, -1));
    for (int i = 0; i < r; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < c; j++) {
            if (s[j] == 'O') a[i][j] = 3;
        }
    }

    for (int t = 1; t <= n; t++) {
        if (t % 2 == 1) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (a[i][j] > 0) a[i][j]--;
                }
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (a[i][j] == 0) {
                        for (int k = 0; k < 4; k++) {
                            int nxti = i + dx[k];
                            int nxtj = j + dy[k];
                            if (nxti < 0 || nxti >= r || nxtj < 0 || nxtj >= c || a[nxti][nxtj] == 0) continue;
                            a[nxti][nxtj] = -1;
                        }
                        a[i][j] = -1;
                    }
                }
            }
        } else {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (a[i][j] == -1) a[i][j] = 3;
                    else a[i][j]--;
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] == -1) cout << '.';
            else cout << 'O';
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