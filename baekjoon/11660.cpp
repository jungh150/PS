#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            s[i][j] = s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1] + a[i][j];
        }
    }

    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1] << '\n';
    }
}