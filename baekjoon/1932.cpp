#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<int>> d(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    int ans = a[0][0];
    d[0][0] = a[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j < i) d[i][j] = max(d[i - 1][j] + a[i][j], d[i][j]);
            if (j > 0) d[i][j] = max(d[i - 1][j - 1] + a[i][j], d[i][j]);
            if (d[i][j] > ans) ans = d[i][j];
        }
    }

    cout << ans << '\n';
}