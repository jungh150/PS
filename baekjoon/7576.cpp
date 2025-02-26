#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
vector<vector<int>> box;
vector<vector<int>> ans;
int m, n;

void bfs() {
    queue<pair<int, int>> q;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (box[i][j] == 1) {
                q.emplace(i, j);
                ans[i][j] = 0;
            }
        }
    }

    while (!q.empty()) {
        int curi = q.front().first;
        int curj = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int ni = curi + dx[k];
            int nj = curj + dy[k];
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && box[ni][nj] == 0) {
                q.emplace(ni, nj);
                box[ni][nj] = 1;
                ans[ni][nj] = ans[curi][curj] + 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n;
    box = vector<vector<int>>(n, vector<int>(m));
    ans = vector<vector<int>>(n, vector<int>(m, -1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> box[i][j];
        }
    }

    bfs();

    int maxa = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (box[i][j] == -1) continue;
            if (ans[i][j] == -1) {
                cout << -1 << '\n';
                return 0;
            } else {
                maxa = max(maxa, ans[i][j]);
            }
        }
    }

    cout << maxa << '\n';
}