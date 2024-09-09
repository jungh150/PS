#include <iostream>
#include <vector>
using namespace std;

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        bool chk[101] = {};

        vector<vector<int>> g(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> g[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (chk[g[i][j]]) continue;
                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        if (g[ni][nj] == g[i][j]) {
                            chk[g[i][j]] = true;
                            break;
                        }
                    }
                }
            }
        }

        int cnt = 0;
        for (bool b: chk) if (b) cnt++;
        cout << cnt << '\n';
    }
}