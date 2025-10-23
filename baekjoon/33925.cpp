#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, j, s, h, k;
    cin >> n >> j >> s >> h >> k;

    vector<string> m(3);
    for (int i = 0; i < 3; i++) cin >> m[i];

    int j1cnt = 0;
    int j2cnt = 0;
    int scnt = 0;
    for (int i = 0; i < n; i++) {
        if (m[0][i] == '.' && m[1][i] == '.' && m[2][i] == '^') j1cnt++;
        else if (m[0][i] == '.' && m[1][i] == '^' && m[2][i] == '^') j2cnt++;
        else if (m[0][i] == 'v' && m[1][i] == 'v' && m[2][i] == '.') scnt++;
    }

    int cnt = 0;
    if (j >= j1cnt) {
        j -= j1cnt;
        cnt += max(j2cnt - j / 2, 0);
    } else {
        cnt += j2cnt;
        cnt += (j1cnt - j);
    }
    cnt += max(scnt - s, 0);

    h -= k * cnt;
    if (h > 0) cout << h << '\n';
    else cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}