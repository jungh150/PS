#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> b;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, t;
    cin >> n >> t;

    b = vector<vector<bool>>(n, vector<bool>(n, false));
    bool chk;
    int ans;

    for (int tnum = 1; tnum <= t; tnum++) {
        int x;
        cin >> x;
        x--;
        int r = x / n;
        int c = x % n;
        b[r][c] = true;

        chk = true;
        for (int i = 0; i < n; i++) {
            if (!b[r][i]) {
                chk = false;
                break;
            }
        }
        if (chk) {
            ans = tnum;
            break;
        }

        chk = true;
        for (int i = 0; i < n; i++) {
            if (!b[i][c]) {
                chk = false;
                break;
            }
        }
        if (chk) {
            ans = tnum;
            break;
        }

        chk = true;
        for (int i = 0; i < n; i++) {
            if (!b[i][i]) {
                chk = false;
                break;
            }
        }
        if (chk) {
            ans = tnum;
            break;
        }

        chk = true;
        for (int i = 0; i < n; i++) {
            if (!b[i][n - i - 1]) {
                chk = false;
                break;
            }
        }
        if (chk) {
            ans = tnum;
            break;
        }
    }

    if (chk) {
        cout << ans << '\n';
    } else {
        cout << -1 << '\n';
    }
}