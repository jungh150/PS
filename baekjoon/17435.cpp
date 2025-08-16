#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int m;
    cin >> m;

    // sp[i][j]: i번 정점에서 2^j번 이동한 정점
    vector<vector<int>> sp(m + 1, vector<int>(20));
    for (int i = 1; i < m + 1; i++) cin >> sp[i][0];

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i < m + 1; i++) {
            sp[i][j] = sp[sp[i][j - 1]][j - 1];
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int n, x;
        cin >> n >> x;
        int cur = x;
        for (int j = 0; j < 20; j++) {
            if (n & (1 << j)) cur = sp[cur][j];
        }
        cout << cur << '\n';
    }
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