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

    int tc;
    cin >> tc;

    while (tc--) {
        int h, w;
        cin >> h >> w;

        vector<string> m(h);
        vector<vector<bool>> chk(h, vector<bool>(w, false));
        vector<bool> open(26, false);
        queue<pair<int, int>> q;
        int cnt = 0;

        // 입력 받으면서 빈칸 혹은 열쇠가 있는 칸 혹은 문서 있는 칸 체크 (시작할 수 있는 지점)
        for (int i = 0; i < h; i++) {
            cin >> m[i];
            if (i == 0 || i == h - 1) {
                for (int j = 0; j < w; j++) {
                    if (m[i][j] == '.') {
                        q.emplace(i, j);
                        chk[i][j] = true;
                    } else if (m[i][j] >= 'a' && m[i][j] <= 'z') {
                        open[m[i][j] - 'a'] = true;
                        q.emplace(i, j);
                        chk[i][j] = true;
                    } else if (m[i][j] == '$') {
                        q.emplace(i, j);
                        chk[i][j] = true;
                        cnt++;
                    }
                }
            } else {
                if (m[i][0] == '.') {
                    q.emplace(i, 0);
                    chk[i][0] = true;
                } else if (m[i][0] >= 'a' && m[i][0] <= 'z') {
                    open[m[i][0] - 'a'] = true;
                    q.emplace(i, 0);
                    chk[i][0] = true;
                } else if (m[i][0] == '$') {
                    q.emplace(i, 0);
                    chk[i][0] = true;
                    cnt++;
                }
                if (m[i][w - 1] == '.') {
                    q.emplace(i, w - 1);
                    chk[i][w - 1] = true;
                } else if (m[i][w - 1] >= 'a' && m[i][w - 1] <= 'z') {
                    open[m[i][w - 1] - 'a'] = true;
                    q.emplace(i, w - 1);
                    chk[i][w - 1] = true;
                } else if (m[i][w - 1] == '$') {
                    q.emplace(i, w - 1);
                    chk[i][w - 1] = true;
                    cnt++;
                }
            }
        }

        // 이미 가지고 있는 열쇠를 입력 받음
        string keys;
        cin >> keys;
        if (keys != "0") {
            for (char key: keys) open[key - 'a'] = true;
        }

        // 빌딩 가장자리 중 열 수 있는 문 체크 (시작할 수 있는 지점)
        for (int i = 0; i < h; i++) {
            if (i == 0 || i == h - 1) {
                for (int j = 0; j < w; j++) {
                    if (m[i][j] >= 'A' && m[i][j] <= 'Z' && open[m[i][j] - 'A']) {
                        q.emplace(i, j);
                        chk[i][j] = true;
                    }
                }
            } else {
                if (m[i][0] >= 'A' && m[i][0] <= 'Z' && open[m[i][0] - 'A']) {
                    q.emplace(i, 0);
                    chk[i][0] = true;
                }
                if (m[i][w - 1] >= 'A' && m[i][w - 1] <= 'Z' && open[m[i][w - 1] - 'A']) {
                    q.emplace(i, w - 1);
                    chk[i][w - 1] = true;
                }
            }
        }

        // 너비 우선 탐색 시작
        while (!q.empty()) {
            int curx = q.front().first;
            int cury = q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nxtx = curx + dx[i];
                int nxty = cury + dy[i];
                if (nxtx >= 0 && nxtx < h && nxty >= 0 && nxty < w && !chk[nxtx][nxty]) {
                    if (m[nxtx][nxty] == '$') {
                        cnt++;
                        q.emplace(nxtx, nxty);
                        chk[nxtx][nxty] = true;
                    } else if (m[nxtx][nxty] >= 'a' && m[nxtx][nxty] <= 'z') {
                        open[m[nxtx][nxty] - 'a'] = true;
                        q.emplace(nxtx, nxty);
                        chk[nxtx][nxty] = true;
                    } else if (m[nxtx][nxty] >= 'A' && m[nxtx][nxty] <= 'Z' && open[m[nxtx][nxty] - 'A']) {
                        q.emplace(nxtx, nxty);
                        chk[nxtx][nxty] = true;
                    }
                }
            }
        }

        cout << cnt << '\n';
    }
}