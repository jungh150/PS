#include <iostream>
#include <vector>
using namespace std;

vector<string> a;

bool chk_col(int r, int c) {
    for (int i = 0; i < 8; i++) {
        if (i == r) continue;
        if (a[i][c] == '*') return true;
    }
    return false;
}

bool chk_row(int r, int c) {
    for (int j = 0; j < 8; j++) {
        if (j == c) continue;
        if (a[r][j] == '*') return true;
    }
    return false;
}

bool chk_ltor(int r, int c) {
    for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) {
        if (a[i][j] == '*') return true;
    }
    for (int i = r + 1, j = c + 1; i < 8 && j < 8; i++, j++) {
        if (a[i][j] == '*') return true;
    }
    return false;
}

bool chk_rtol(int r, int c) {
    for (int i = r - 1, j = c + 1; i >= 0 && j < 8; i--, j++) {
        if (a[i][j] == '*') return true;
    }
    for (int i = r + 1, j = c - 1; i < 8 && j >= 0; i++, j--) {
        if (a[i][j] == '*') return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    a = vector<string>(8);
    for (int i = 0; i < 8; i++) cin >> a[i];

    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (a[i][j] == '*') {
                cnt++;
                if (chk_col(i, j) || chk_row(i, j) || chk_ltor(i, j) || chk_rtol(i, j)) {
                    cout << "invalid\n";
                    return 0;
                }
            }
        }
    }

    if (cnt != 8) {
        cout << "invalid\n";
        return 0;
    }

    cout << "valid\n";
}