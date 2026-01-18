#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;

    int p[100001][3];
    for (int i = 0; i < n; i++) {
        cin >> p[i][0] >> p[i][1] >> p[i][2];
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        ll x, y, z, r;
        cin >> x >> y >> z >> r;

        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (r * r >= (x - p[j][0]) * (x - p[j][0]) + (y - p[j][1]) * (y - p[j][1]) + (z - p[j][2]) * (z - p[j][2])) cnt++;
        }
        cout << cnt << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}