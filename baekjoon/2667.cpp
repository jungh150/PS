#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<bool>> g;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    int n;
    cin >> n;

    g = vector<vector<bool>>(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < n; j++) {
            g[i][j] = str[j] - '0';
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j]) {
                queue<pair<int, int>> q;
                q.emplace(i, j);
                g[i][j] = false;
                int cnt = 1;
                while (!q.empty()) {
                    // auto [ci, cj] = q.front();
                    int ci = q.front().first;
                    int cj = q.front().second;
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int ni = ci + dx[k];
                        int nj = cj + dy[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && g[ni][nj]) {
                            q.emplace(ni, nj);
                            g[ni][nj] = false;
                            cnt++;
                        }
                    }
                }
                ans.push_back(cnt);
            }
        }
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int x: ans) cout << x << '\n';
}