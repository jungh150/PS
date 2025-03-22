#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    cin >> m >> k;

    vector<vector<int>> b(m, vector<int>(k));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            cin >> b[i][j];
        }
    }

    vector<vector<int>> c(n, vector<int>(k, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < m; l++) {
                c[i][j] += a[i][l] * b[l][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << c[i][j] << ' ';
        }
        cout << '\n';
    }
}