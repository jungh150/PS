#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c, zr, zc;
    cin >> r >> c  >> zr >> zc;

    int nr = r * zr;
    int nc = c * zc;

    vector<string> orin(r);
    vector<vector<char>> newn(nr, vector<char>(nc));

    for (int i = 0; i < r; i++) cin >> orin[i];

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            newn[i][j] = orin[i / zr][j / zc];
            cout << newn[i][j];
        }
        cout << '\n';
    }
}