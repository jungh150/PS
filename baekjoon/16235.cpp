#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> b(n + 1, vector<int>(n + 1, 5));
    vector<vector<vector<int>>> tr(n + 1, vector<vector<int>>(n + 1));

    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        tr[x][y].push_back(z);
    }

    while (k--) {
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                // 봄
                sort(tr[i][j].begin(), tr[i][j].end());
                int sz = tr[i][j].size();
                int idx = sz;
                for (int x = 0; x < sz; x++) {
                    if (b[i][j] >= tr[i][j][x]) {
                        b[i][j] -= tr[i][j][x];
                        tr[i][j][x]++;
                    } else {
                        idx = x;
                        break;
                    }
                }
                // 여름
                for (int x = sz - 1; x >= idx; x--) {
                    b[i][j] += tr[i][j][x] / 2;
                    tr[i][j].pop_back();
                }
            }
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < n + 1; j++) {
                // 가을
                int sz = tr[i][j].size();
                for (int x = 0; x < sz; x++) {
                    if (tr[i][j][x] % 5 == 0) {
                        for (int z = 0; z < 8; z++) {
                            int ni = i + dx[z];
                            int nj = j + dy[z];
                            if (ni < 1 || ni > n || nj < 1 || nj > n) continue;
                            tr[ni][nj].push_back(1);
                        }
                    }
                }
                // 겨울
                b[i][j] += a[i][j];
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            ans += tr[i][j].size();
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