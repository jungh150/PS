#include <iostream>
#include <vector>
using namespace std;

int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (true) {
        int r, c;
        cin >> r >> c;
        if (r == 0 && c == 0) return 0;

        vector<string> m(r);
        for (int i = 0; i < r; i++) cin >> m[i];

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (m[i][j] == '*') {
                    cout << '*';
                } else {
                    int tmp = 0;
                    for (int k = 0; k < 8; k++) {
                        int nxti = i + dx[k];
                        int nxtj = j + dy[k];
                        if (nxti >= 0 && nxti < r && nxtj >= 0 && nxtj < c && m[nxti][nxtj] == '*') {
                            tmp++;
                        }
                    }
                    cout << tmp;
                }
            }
            cout << '\n';
        }
    }
}