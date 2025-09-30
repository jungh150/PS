#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> obs(n);
    for (int i = 0; i < n; i++) cin >> obs[i].first >> obs[i].second;

    string op;
    cin >> op;

    int curx = 0;
    int cury = 0;
    for (int i = 0; i < k; i++) {
        int nxtx, nxty;
        if (op[i] == 'U') {
            nxtx = curx;
            nxty = cury + 1;
        } else if (op[i] == 'D') {
            nxtx = curx;
            nxty = cury - 1;
        } else if (op[i] == 'R') {
            nxtx = curx + 1;
            nxty = cury;
        } else if (op[i] == 'L') {
            nxtx = curx - 1;
            nxty = cury;
        }

        bool upd = true;
        for (auto [ox, oy]: obs) {
            if (ox == nxtx && oy == nxty) {
                upd = false;
                break;
            }
        }

        if (upd) {
            curx = nxtx;
            cury = nxty;
        }
    }

    cout << curx << ' ' << cury << '\n';
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