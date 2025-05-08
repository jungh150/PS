#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c;
    cin >> r >> c;

    int nr = r * 2;
    int nc = c * 2;

    vector<vector<char>> arr(nr, vector<char>(nc));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char c;
            cin >> c;
            arr[i][j] = c;
        }
    }

    // 좌우 대칭
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            arr[i][nc - j - 1] = arr[i][j];
        }
    }

    // 상하 대칭
    for (int i = 0; i < r; i++) {
        arr[nr - i - 1] = arr[i];
    }

    int a, b;
    cin >> a >> b;

    a--;
    b--;

    if (arr[a][b] == '.') arr[a][b] = '#';
    else if (arr[a][b] == '#') arr[a][b] = '.';

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            cout << arr[i][j];
        }
        cout << '\n';
    }
}