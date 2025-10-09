#include <iostream>
#include <vector>
using namespace std;

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(m, vector<int>(3));
    vector<vector<vector<bool>>> grid(n + 1, vector<vector<bool>>(n + 1, vector<bool>(n + 1, false)));

    for (int i = 0; i < m; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        grid[a[i][0]][a[i][1]][a[i][2]] = true;
    }

    int ans = 0;

    for (int i = 0; i < m; i++) {
        bool flag = true;
        for (int k = 0; k < 6; k++) {
            if ((a[i][0] + dx[k] < 1) || (a[i][0] + dx[k] > n) || (a[i][1] + dy[k] < 1) || (a[i][1] + dy[k] > n) || (a[i][2] + dz[k] < 1) || (a[i][2] + dz[k] > n)
                || !grid[a[i][0] + dx[k]][a[i][1] + dy[k]][a[i][2] + dz[k]]) {
                flag = false;
                break;
            }
        }
        if (flag) ans++;
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