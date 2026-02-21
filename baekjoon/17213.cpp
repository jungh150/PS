#include <iostream>
#include <vector>
using namespace std;

void solve() {
    vector<vector<int>> c(30, vector<int>(30, 1));
    for (int i = 0; i < 30; i++) c[i][0] = c[i][i] = 1;
    for (int i = 2; i < 30; i++) {
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }

    int n, m;
    cin >> n >> m;
    cout << c[m - 1][n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}