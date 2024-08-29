#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1, vector<int>(m + 1));
    
    for (int i = 1; i < n + 1; i++) cin >> g[i][0];
    for (int i = 1; i < m + 1; i++) cin >> g[0][i];

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (g[i - 1][j] == g[i][j - 1]) g[i][j] = 0;
            else g[i][j] = 1;
        }
    }

    cout << g[n][m] << '\n';
}