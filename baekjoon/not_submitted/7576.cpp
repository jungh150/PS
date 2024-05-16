#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dn[4] = {0, 0, -1, 1};
int dm[4] = {-1, 1, 0, 0};
vector<vector<int>> box;
int m, n;
int t = 0;

bool check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (box[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void bfs() {
    queue<vector<int>> q;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (box[i][j] == 1) {
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        int tmp = q.size();
        for (int i = 0; i < tmp; i++) {
            vector<int> cur = q.front();
            q.pop();
            for (int x = 0; x < 4; x++) {
                int ni = cur[0] + dn[x];
                int nj = cur[1] + dm[x];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && box[ni][nj] == 0) {
                    q.push({ni, nj});
                    box[ni][nj] = 1;
                }
            }
        }
        t++;
        if (check()) {
            break;
        }
    }

    if (!check()) {
        t = -1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> m >> n;
    box = vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> box[i][j];
        }
    }

    if (check()) {
        t = 0;
    }
    else {
        bfs();
    }

    cout << t << '\n';
}