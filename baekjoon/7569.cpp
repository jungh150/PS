#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int dh[6] = {0, 0, 0, 0, 1, -1};
int dn[6] = {1, -1, 0, 0, 0, 0};
int dm[6] = {0, 0, -1, 1, 0, 0};
vector<vector<vector<int>>> box;
int m, n, h;
int t = 0;

bool check() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (box[i][j][k] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void bfs() {
    queue<vector<int>> q;
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (box[i][j][k] == 1) {
                    q.push({i, j, k});
                }
            }
        }
    }

    while (!q.empty()) {
        int tmp = q.size();
        for (int i = 0; i < tmp; i++) {
            vector<int> cur = q.front();
            q.pop();
            for (int x = 0; x < 6; x++) {
                int ni = cur[0] + dh[x];
                int nj = cur[1] + dn[x];
                int nk = cur[2] + dm[x];
                if (ni >= 0 && ni < h && nj >= 0 && nj < n && nk >= 0 && nk < m && box[ni][nj][nk] == 0) {
                    q.push({ni, nj, nk});
                    box[ni][nj][nk] = 1;
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

    cin >> m >> n >> h;
    box = vector<vector<vector<int>>>(h, vector<vector<int>>(n, vector<int>(m)));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                cin >> box[i][j][k];
            }
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