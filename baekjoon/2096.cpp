#include <iostream>
#include <vector>
using namespace std;

int const INTMAX = 1000000000;
int const MAX_N = 100000;
int m[MAX_N][3];
int dpmax[2][3];
int dpmin[2][3];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> m[i][j];
        }
    }

    for (int j = 0; j < 3; j++) {
        dpmax[0][j] = m[0][j];
        dpmin[0][j] = m[0][j];
    }

    for (int i = 1; i < n; i++) {
        dpmax[1][0] = max(dpmax[0][0], dpmax[0][1]) + m[i][0];
        dpmax[1][1] = max(max(dpmax[0][0], dpmax[0][1]), dpmax[0][2]) + m[i][1];
        dpmax[1][2] = max(dpmax[0][1], dpmax[0][2]) + m[i][2];

        dpmin[1][0] = min(dpmin[0][0], dpmin[0][1]) + m[i][0];
        dpmin[1][1] = min(min(dpmin[0][0], dpmin[0][1]), dpmin[0][2]) + m[i][1];
        dpmin[1][2] = min(dpmin[0][1], dpmin[0][2]) + m[i][2];

        for (int j = 0; j < 3; j++) {
            dpmax[0][j] = dpmax[1][j];
            dpmin[0][j] = dpmin[1][j];
        }
    }

    cout << max(max(dpmax[0][0], dpmax[0][1]), dpmax[0][2]) << ' ';
    cout << min(min(dpmin[0][0], dpmin[0][1]), dpmin[0][2]) << '\n';
}