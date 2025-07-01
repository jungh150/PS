#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<vector<vector<int>>> w(51, vector<vector<int>>(51, vector<int>(51, 1)));

    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            for (int k = 1; k <= 50; k++) {
                if (i < j && j < k) {
                    w[i][j][k] = w[i][j][k - 1] + w[i][j - 1][k - 1] - w[i][j - 1][k];
                } else {
                    w[i][j][k] = w[i - 1][j][k] + w[i - 1][j - 1][k] + w[i - 1][j][k - 1] - w[i - 1][j - 1][k - 1];
                }
            }
        }
    }

    while (1) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1) break;
        cout << "w(" << a << ", " << b << ", " << c << ") = ";
        if (a <= 0 || b <= 0 || c <= 0) cout << 1 << '\n';
        else if (a > 20 || b > 20 || c > 20) cout << w[20][20][20] << '\n';
        else cout << w[a][b][c] << '\n';
    }
}