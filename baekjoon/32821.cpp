#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<vector<int>> grid;
vector<int> a;
vector<int> b;
int MAX_VAL = 1e8;

int bfs(int sx, int sflip) {
    a = vector<int>(n + m - 1, -1); // a 대각선(i+j=x)의 flip 여부
    b = vector<int>(n + m - 1, -1); // b 대각선(i-j=x)의 flip 여부 (offset = m - 1)
    
    queue<vector<int>> q;
    int cnt = 0;

    a[sx] = sflip;
    q.push({0, sx, sflip});
    if (sflip == 1) cnt++;

    while (!q.empty()) {
        int type = q.front()[0];
        int x = q.front()[1];
        int flip = q.front()[2];
        q.pop();
        
        if (type == 0) { // a 대각선
            for (int i = 0; i < n; i++) { // a 대각선 위의 칸들 탐색
                int j = x - i;
                if (j < 0 || j >= m) continue;
                if (b[i - j + (m - 1)] == -1) { // b 대각선 방문한 적 없으면
                    if ((grid[i][j] + a[i + j]) % 2 == 0) { // 이미 0이면
                        b[i - j + (m - 1)] = 0; // b 대각선을 not flip으로 결정
                        q.push({1, i - j, 0});
                    } else { // 1이면
                        b[i - j + (m - 1)] = 1; // b 대각선을 flip으로 결정
                        q.push({1, i - j, 1});
                        cnt++;
                    }
                } else { // b 대각선 방문한 적 있으면
                    if ((grid[i][j] + a[i + j] + b[i - j + (m - 1)]) % 2 == 1) return MAX_VAL; // 모순
                }
            }
        } else if (type == 1) { // b 대각선
            for (int i = 0; i < n; i++) { // b 대각선 위의 칸들 탐색
                int j = i - x;
                if (j < 0 || j >= m) continue;
                if (a[i + j] == -1) { // a 대각선 방문한 적 없으면
                    if ((grid[i][j] + b[i - j + (m - 1)]) % 2 == 0) { // 이미 0이면
                        a[i + j] = 0; // a 대각선을 not flip으로 결정
                        q.push({0, i + j, 0});
                    } else {
                        a[i + j] = 1; // a 대각선을 flip으로 결정
                        q.push({0, i + j, 1});
                        cnt++;
                    }
                } else { // a 대각선 방문한 적 있으면
                    if ((grid[i][j] + a[i + j] + b[i - j + (m - 1)]) % 2 == 1) return MAX_VAL; // 모순
                }
            }
        }
    }
    return cnt;
}

void solve() {
    cin >> n >> m;

    grid = vector<vector<int>>(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // 예외 처리: 1의 개수만 세기
    if (n == 1 || m == 1) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) cnt++;
            }
        }
        cout << cnt << '\n';
        return;
    }

    // a 대각선(i+j=0)을 not flip으로 결정, flip으로 결정
    int ans1 = min(bfs(0, 0), bfs(0, 1));
    // a 대각선(i+j=1)을 not flip으로 결정, flip으로 결정
    int ans2 = min(bfs(1, 0), bfs(1, 1));

    int ans = ans1 + ans2;
    if (ans > MAX_VAL) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}