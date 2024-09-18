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
    int ri, rj, bi, bj;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            g[i][j] = s[j];
            if (g[i][j] == 'R') {
                ri = i;
                rj = j;
            }
            if (g[i][j] == 'B') {
                bi = i;
                bj = j;
            }
        }
    }

    queue<vector<int>> q;
    vector<vector<vector<vector<bool>>>> visited(n, vector<vector<vector<bool>>>(m, vector<vector<bool>>(n, vector<bool>(m, false))));
    q.push(vector<int>{ri, rj, bi, bj, 0}); // red i, red j, blue i, blue j, cnt
    visited[ri][rj][bi][bj] = true;
    
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            vector<int> nxt(5);
            nxt[0] = cur[0] + dx[k];
            nxt[1] = cur[1] + dy[k];
            nxt[2] = cur[2] + dx[k];
            nxt[3] = cur[3] + dy[k];
            nxt[4] = cur[4] + 1;
            if (nxt[4] > 10) {
                cout << -1 << '\n';
                return 0;
            }

            int fixedri = -1;
            int fixedrj = -1;
            int fixedbi = -1;
            int fixedbj = -1;
            bool holer = false;
            bool holeb = false;

            while (fixedri == -1 || fixedbi == -1) {
                // move red
                if (!holer && fixedri == -1) {
                    if (g[nxt[0]][nxt[1]] == '#') {
                        nxt[0] -= dx[k];
                        nxt[1] -= dy[k];
                        if (nxt[0] != fixedbi || nxt[1] != fixedbj) {
                            fixedri = nxt[0];
                            fixedrj = nxt[1];
                        }
                    } else if (g[nxt[0]][nxt[1]] == 'O') {
                        fixedri = nxt[0];
                        fixedrj = nxt[1];
                        holer = true;
                    } else { // '.' or 'R' or 'B'
                        if (nxt[0] == fixedbi && nxt[1] == fixedbj) {
                            nxt[0] -= dx[k];
                            nxt[1] -= dy[k];
                            fixedri = nxt[0];
                            fixedrj = nxt[1];
                        } else {
                            nxt[0] += dx[k];
                            nxt[1] += dy[k];
                        }
                    }
                }

                // move blue
                if (!holeb && fixedbi == -1) {
                    if (g[nxt[2]][nxt[3]] == '#') {
                        nxt[2] -= dx[k];
                        nxt[3] -= dy[k];
                        if (nxt[2] != fixedri || nxt[3] != fixedrj) {
                            fixedbi = nxt[2];
                            fixedbj = nxt[3];
                        }
                    } else if (g[nxt[2]][nxt[3]] == 'O') {
                        fixedbi = nxt[2];
                        fixedbj = nxt[3];
                        holeb = true;
                    } else { // '.' or 'R' or 'B'
                        if (nxt[2] == fixedri && nxt[3] == fixedrj) {
                            nxt[2] -= dx[k];
                            nxt[3] -= dy[k];
                            fixedbi = nxt[2];
                            fixedbj = nxt[3];
                        } else {
                            nxt[2] += dx[k];
                            nxt[3] += dy[k];
                        }
                    }
                }
            }

            if (holer && !holeb) {
                cout << nxt[4] << '\n';
                return 0;
            } else if (!holeb) {
                if (!visited[nxt[0]][nxt[1]][nxt[2]][nxt[3]]) {
                    visited[nxt[0]][nxt[1]][nxt[2]][nxt[3]] = true;
                    q.push(vector<int>{nxt[0], nxt[1], nxt[2], nxt[3], nxt[4]});
                }
            }
        }
    }
    
    cout << -1 << '\n';
}