#include <iostream>
#include <vector>
using namespace std;

int r, c, t;
vector<vector<int>> a;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool isclear() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] > 0) return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ap1 = -1;
    int ap2 = -1;
    cin >> r >> c >> t;

    a = vector<vector<int>>(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
            if (a[i][j] == -1) {
                if (ap1 == -1) ap1 = i;
                else ap2 = i;
            }
        }
    }

    while (t--) {
        // 1. 미세먼지 확산
        vector<vector<int>> tmp(r, vector<int>(c, 0));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] <= 0) continue;
                int dif = a[i][j] / 5;  // 확산되는 양
                int cnt = 0;  // 확산되는 방향의 개수
                for (int k = 0; k < 4; k++) {
                    int nxti = i + dx[k];
                    int nxtj = j + dy[k];
                    if (nxti >= 0 && nxti < r && nxtj >= 0 && nxtj < c && a[nxti][nxtj] >= 0) {
                        tmp[nxti][nxtj] += dif;
                        cnt++;
                    }
                }
                tmp[i][j] += (a[i][j] - dif * cnt);  // 남는 양
            }
        }

        swap(a, tmp);

        // 2. 공기청정기 작동
        int ai = ap1 - 1;
        int aj = 0;

        // 아래로
        while (ai >= 0) {
            a[ai + 1][aj] = a[ai][aj];
            ai--;
        }
        ai++;
        aj++;
        // 왼쪽으로
        while (aj < c) {
            a[ai][aj - 1] = a[ai][aj];
            aj++;
        }
        aj--;
        ai++;
        // 위로
        while (ai <= ap1) {
            a[ai - 1][aj] = a[ai][aj];
            ai++;
        }
        ai--;
        aj--;
        // 오른쪽으로
        while (aj > 0) {
            a[ai][aj + 1] = a[ai][aj];
            aj--;
        }
        a[ai][aj] = -1;
        a[ai][aj + 1] = 0;

        ai = ap2 + 1;
        aj = 0;

        // 위로
        while (ai < r) {
            a[ai - 1][aj] = a[ai][aj];
            ai++;
        }
        ai--;
        aj++;
        // 왼쪽으로
        while (aj < c) {
            a[ai][aj - 1] = a[ai][aj];
            aj++;
        }
        aj--;
        ai--;
        // 아래로
        while (ai >= ap2) {
            a[ai + 1][aj] = a[ai][aj];
            ai--;
        }
        ai++;
        aj--;
        // 오른쪽으로
        while (aj > 0) {
            a[ai][aj + 1] = a[ai][aj];
            aj--;
        }
        a[ai][aj] = -1;
        a[ai][aj + 1] = 0;
    }

    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i][j] > 0) ans += a[i][j];
        }
    }

    cout << ans << '\n';
}