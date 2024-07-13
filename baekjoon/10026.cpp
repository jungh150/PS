#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<string> g;

bool chk1(int ci, int cj, int ni, int nj) {
    if (g[ci][cj] == g[ni][nj]) return true;
    else return false;
}

bool chk2(int ci, int cj, int ni, int nj) {
    if (g[ci][cj] == g[ni][nj]) {
        return true;
    } else {
        if (g[ci][cj] == 'R' && g[ni][nj] == 'G') {
            return true;
        } else if (g[ci][cj] == 'G' && g[ni][nj] == 'R') {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    int n;
    cin >> n;

    g = vector<string>(n);
    for (int i = 0; i < n; i++) cin >> g[i];

    vector<vector<bool>> vst1(n, vector<bool>(n, false));
    int cnt1 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vst1[i][j]) {
                cnt1++;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                vst1[i][j] = true;
                while (!q.empty()) {
                    // auto [ci, cj] = q.front();
                    int ci = q.front().first;
                    int cj = q.front().second;
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int ni = ci + dx[k];
                        int nj = cj + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && !vst1[ni][nj]) {
                            if (chk1(ci, cj, ni, nj)) {
                                q.emplace(ni, nj);
                                vst1[ni][nj] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    vector<vector<bool>> vst2(n, vector<bool>(n, false));
    int cnt2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vst2[i][j]) {
                cnt2++;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                vst2[i][j] = true;
                while (!q.empty()) {
                    // auto [ci, cj] = q.front();
                    int ci = q.front().first;
                    int cj = q.front().second;
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int ni = ci + dx[k];
                        int nj = cj + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && !vst2[ni][nj]) {
                            if (chk2(ci, cj, ni, nj)) {
                                q.emplace(ni, nj);
                                vst2[ni][nj] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << cnt1 << ' ' << cnt2 << '\n';
}