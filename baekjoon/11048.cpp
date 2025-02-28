#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> a;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    a = vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i < n; i++) a[i][0] += a[i - 1][0];
    for (int j = 1; j < m; j++) a[0][j] += a[0][j - 1];

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            a[i][j] += max(a[i - 1][j], a[i][j - 1]);
        }
    }

    cout << a[n - 1][m - 1] << '\n';
}