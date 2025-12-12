#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx1[] = {-1, -1, 0, 0, 1, 1, 0, 0};
int dy1[] = {0, 0, 1, 1, 0, 0, -1, -1};
int dx2[] = {-1, -1, -1, 1, 1, 1, 1, -1};
int dy2[] = {-1, 1, 1, 1, 1, -1, -1, -1};

void solve() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    vector<vector<int>> vst(10, vector<int>(9, -1));
    queue<pair<int, int>> q;

    vst[r1][c1] = 0;
    q.emplace(r1, c1);
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int k = 0; k < 8; k++) {
            int nxtr = r + dx1[k] + 2 * dx2[k];
            int nxtc = c + dy1[k] + 2 * dy2[k];
            if (r + dx1[k] == r2 && c + dy1[k] == c2) continue;
            if (r + dx1[k] + dx2[k] == r2 && c + dy1[k] + dy2[k] == c2) continue;
            if (nxtr >= 0 && nxtr < 10 && nxtc >= 0 && nxtc < 9 && vst[nxtr][nxtc] == -1) {
                vst[nxtr][nxtc] = vst[r][c] + 1;
                q.emplace(nxtr, nxtc);
            }
        }
    }

    cout << vst[r2][c2] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}