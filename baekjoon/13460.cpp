#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    int ri, rj, bi, bj, hi, hj;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'R') {
                ri = i;
                rj = j;
            }
            if (g[i][j] == 'B') {
                bi = i;
                bj = j;
            }
            if (g[i][j] == 'O') {
                hi = i;
                hj = j;
            }
        }
    }

    queue<vector<int>> q;
    q.emplace(ri, rj, bi, bj, 0);
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            vector<int> nxt = q.front();
            for (int i = 0; i < 5; i++) nxt[i] = cur[i];

            while (g[nxt[0]][nxt[1]] == '.') {
                nxt[0] += dx[k];
                nxt[1] += dy[k];
            }
            if (nxt[0] < 0 || nxt[0] >= n || nxt[1] < 0 || nxt[1] >= m) continue;
            
            while (g[nxt[2]][nxt[3]] == '.') {
                nxt[2] += dx[k];
                nxt[3] += dy[k];
            }
            if (nxt[2] < 0 || nxt[2] >= n || nxt[3] < 0 || nxt[3] >= m) continue;
        }
    }
}