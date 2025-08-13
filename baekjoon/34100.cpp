#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<string> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        bool psb = true;

        for (int j = 0; j < m - 1; j++) {
            for (int i = n - 1; i > 0; i--) {
                if (a[i][j] != '.') continue;
                if (a[i - 1][j] == '.') {
                    if (a[i][j + 1] != '.') {
                        psb = false;
                        break;
                    }
                    a[i - 1][j] = 'a';
                    a[i][j] = 'a';
                    a[i][j + 1] = 'a';
                } else {
                    if (a[i - 1][j + 1] != '.' || a[i][j + 1] != '.') {
                        psb = false;
                        break;
                    }
                    a[i - 1][j + 1] = 'b';
                    a[i][j] = 'b';
                    a[i][j + 1] = 'b';
                }
            }
            if (!psb) break;
        }

        for (int i = 0; i < n; i++) {
            if (a[i][m - 1] == '.') {
                psb = false;
                break;
            }
        }

        for (int j = 0; j < m; j++) {
            if (a[0][j] == '.') {
                psb = false;
                break;
            }
        }

        if (psb) {
            for (int i = 0; i < n; i++) cout << a[i] << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}