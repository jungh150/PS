#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<string> a(3 * n);
    for (int i = 0; i < 3 * n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) continue;

            bool up, down, left, right;

            if (i > 0 && a[(i - 1) * 3 + 2][j * 3 + 1] == '#') up = true;
            else up = false;
            if (i < n - 1 && a[(i + 1) * 3][j * 3 + 1] == '#') down = true;
            else down = false;
            if (j > 0 && a[i * 3 + 1][(j - 1) * 3 + 2] == '#') left = true;
            else left = false;
            if (j < m - 1 && a[i * 3 + 1][(j + 1) * 3] == '#') right = true;
            else right = false;

            if (!up && down && !left && right) {
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (!up && down && left && right) {
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (!up && down && left && !right) {
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (up && down && !left && right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (up && down && left && right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (up && down && left && !right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            } else if (up && !down && !left && right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
            } else if (up && !down && left && right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
            } else if (up && !down && left && !right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
            } else if (!up && !down && left && right) {
                a[i * 3 + 1][j * 3] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 2] = '#';
            } else if (up && down && !left && !right) {
                a[i * 3][j * 3 + 1] = '#';
                a[i * 3 + 1][j * 3 + 1] = '#';
                a[i * 3 + 2][j * 3 + 1] = '#';
            }
        }
    }

    for (int i = 0; i < 3 * n; i++) {
        cout << a[i] << '\n';
    }
}