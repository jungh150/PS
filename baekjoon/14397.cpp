#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];

        for (int j = 0; j < m - 1; j++) {
            if (a[i][j] != a[i][j + 1]) ans++;
        }

        if (i == 0) {
            continue;
        } else if (i % 2 == 1) {
            for (int j = 0; j < m; j++) {
                if (j == m - 1) {
                    if (a[i][j] != a[i - 1][j]) ans++;
                } else {
                    if (a[i][j] != a[i - 1][j]) ans++;
                    if (a[i][j] != a[i - 1][j + 1]) ans++;
                }
            }
        } else {
            for (int j = 0; j < m; j++) {
                if (j == 0) {
                    if (a[i][j] != a[i - 1][j]) ans++;
                } else {
                    if (a[i][j] != a[i - 1][j]) ans++;
                    if (a[i][j] != a[i - 1][j - 1]) ans++;
                }
            }
        }
    }

    cout << ans << '\n';
}