#include <iostream>
#include <vector>
using namespace std;

int n, ans;
vector<vector<int>> m;

void move(int d) {
    if (d == 0) { // 위로
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                for (int k = i + 1; k < n; k++) {
                    if (m[k][j] != 0) { // 가장 가까운 칸 찾기
                        if (m[i][j] == m[k][j]) { // 같으면 합치고 끝
                            m[i][j] += m[k][j];
                            m[k][j] = 0;
                            break;
                        } else { // 다르면 이동 후
                            if (m[i][j] == 0) { // 해당 위치에서 계속 반복
                                m[i][j] = m[k][j];
                                m[k][j] = 0;
                            } else { // 반복 끝
                                if (k != i + 1) {
                                    m[i + 1][j] = m[k][j];
                                    m[k][j] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    } else if (d == 1) { // 아래로
        for (int j = 0; j < n; j++) {
            for (int i = n - 1; i >= 0; i--) {
                for (int k = i - 1; k >= 0; k--) {
                    if (m[k][j] != 0) { // 가장 가까운 칸 찾기
                        if (m[i][j] == m[k][j]) { // 같으면 합치고 끝
                            m[i][j] += m[k][j];
                            m[k][j] = 0;
                            break;
                        } else { // 다르면 이동 후
                            if (m[i][j] == 0) { // 해당 위치에서 계속 반복
                                m[i][j] = m[k][j];
                                m[k][j] = 0;
                            } else { // 반복 끝
                                if (k != i - 1) {
                                    m[i - 1][j] = m[k][j];
                                    m[k][j] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    } else if (d == 2) { // 왼쪽으로
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (m[i][k] != 0) { // 가장 가까운 칸 찾기
                        if (m[i][j] == m[i][k]) { // 같으면 합치고 끝
                            m[i][j] += m[i][k];
                            m[i][k] = 0;
                            break;
                        } else { // 다르면 이동 후
                            if (m[i][j] == 0) { // 해당 위치에서 계속 반복
                                m[i][j] = m[i][k];
                                m[i][k] = 0;
                            } else { // 반복 끝
                                if (k != j + 1) {
                                    m[i][j + 1] = m[i][k];
                                    m[i][k] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    } else if (d == 3) { // 오른쪽으로
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= 0; j--) {
                for (int k = j - 1; k >= 0; k--) {
                    if (m[i][k] != 0) { // 가장 가까운 칸 찾기
                        if (m[i][j] == m[i][k]) { // 같으면 합치고 끝
                            m[i][j] += m[i][k];
                            m[i][k] = 0;
                            break;
                        } else { // 다르면 이동 후
                            if (m[i][j] == 0) { // 해당 위치에서 계속 반복
                                m[i][j] = m[i][k];
                                m[i][k] = 0;
                            } else { // 반복 끝
                                if (k != j - 1) {
                                    m[i][j - 1] = m[i][k];
                                    m[i][k] = 0;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void dfs(int cnt) {
    if (cnt == 5) {
        int maxt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                maxt = max(maxt, m[i][j]);
            }
        }
        ans = max(ans, maxt);
        return;
    }

    for (int d = 0; d < 4; d++) {
        vector<vector<int>> backup = m;
        move(d);
        dfs(cnt + 1);
        m = backup;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    m = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }

    dfs(0);

    cout << ans << '\n';
}