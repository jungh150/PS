#include <iostream>
#include <vector>
using namespace std;

char rev[] = {'0', '1', '5', '?', '?', '2', '?', '?', '8', '?'};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char d;
    cin >> d;

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<char>> ans(n, vector<char>(n));
    if (d == 'L' || d == 'R') {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][n - j - 1] = rev[a[i][j]];
            }
        }
    } else if (d == 'U' || d == 'D') {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[n - i - 1][j] = rev[a[i][j]];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}