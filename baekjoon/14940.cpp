#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int diri[] = {1, -1, 0, 0};
    int dirj[] = {0, 0, 1, -1};

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g = vector<vector<int>>(n, vector<int>(m));
    vector<vector<int>> d = vector<vector<int>>(n, vector<int>(m, 0));
    int sa, sb;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 2) {
                sa = i;
                sb = j;
            }
        }
    }

    queue<pair<int, int>> q;
    q.emplace(sa, sb);
    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tmpa = a + diri[i];
            int tmpb = b + dirj[i];
            if (tmpa >= 0 && tmpa < n && tmpb >= 0 && tmpb < m 
                && g[tmpa][tmpb] != 0 && d[tmpa][tmpb] == 0) {
                d[tmpa][tmpb] = d[a][b] + 1;
                q.emplace(tmpa, tmpb);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (d[i][j] == 0 && g[i][j] == 1) {
                d[i][j] = -1;
            }
        }
    }

    d[sa][sb] = 0;

    for (auto &d: d) {
        for (auto d: d) {
            cout << d << ' ';
        }
        cout << '\n';
    }
}