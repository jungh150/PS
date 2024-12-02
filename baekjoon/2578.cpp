#include <iostream>
#include <vector>
using namespace std;

int m[5][5];
int num[25];

int isBingo(int x, int y) {
    int cnttmp = 0;

    bool bingo = true;
    for (int i = 0; i < 5; i++) {
        if (m[i][y] != 0) {
            bingo = false;
            break;
        }
    }
    if (bingo) cnttmp++;

    bingo = true;
    for (int j = 0; j < 5; j++) {
        if (m[x][j] != 0) {
            bingo = false;
            break;
        }
    }
    if (bingo) cnttmp++;

    if (x == y) {
        bingo = true;
        for (int i = 0; i < 5; i++) {
            if (m[i][i] != 0) {
                bingo = false;
                break;
            }
        }
        if (bingo) cnttmp++;
    }

    if (x + y == 4) {
        bingo = true;
        for (int i = 0; i < 5; i++) {
            if (m[i][4 - i] != 0) {
                bingo = false;
                break;
            }
        }
        if (bingo) cnttmp++;
    }

    return cnttmp;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> m[i][j];
        }
    }

    for (int k = 0; k < 25; k++) cin >> num[k];

    int cnt = 0;
    for (int k = 0; k < 25; k++) {
        bool chk = false;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (m[i][j] == num[k]) {
                    m[i][j] = 0;
                    cnt += isBingo(i, j);
                    chk = true;
                    break;
                }
            }
            if (chk) break;
        }
        if (cnt >= 3) {
            cout << k + 1 << '\n';
            break;
        }
    }
}