#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int k;
    cin >> k;

    while (k--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int ans = 0;
        for (int i = x1; i < x2 + 1; i++) {
            for (int j = y1; j < y2 + 1; j++) {
                ans += a[i - 1][j - 1];
            }
        }

        cout << ans << '\n';
    }
}