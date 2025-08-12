#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c, m;
    cin >> r >> c >> m;

    vector<vector<int>> sh(m, vector<int>(5));
    for (int i = 0; i < m; i++) {
        cin >> sh[i][1] >> sh[i][2] >> sh[i][3] >> sh[i][4] >> sh[i][0];
        sh[i][1]--;
        sh[i][2]--;
    }
    
    sort(sh.begin(), sh.end()); // 크기 순으로 정렬

    vector<bool> alive(m, true); // 존재하는 상어인지
    long long ans = 0;

    // 첫번째 낚시 (0번째 열)
    int maxshfirst = -1;
    for (int k = 0; k < m; k++) {
        if (sh[k][2] == 0) {
            if (maxshfirst == -1) {
                maxshfirst = k;
            } else {
                if (sh[k][1] <= sh[maxshfirst][1]) maxshfirst = k;
            }
        }
    }
    if (maxshfirst != -1) {
        ans += sh[maxshfirst][0];
        alive[maxshfirst] = false;
    }

    for (int j = 1; j < c; j++) {
        // 상어 이동
        vector<vector<int>> chk(r, vector<int>(c, -1)); // 해당 칸에 다른 (더 작은) 상어가 있는지
        int maxsh = -1;
        for (int k = 0; k < m; k++) {
            if (!alive[k]) continue;
            int curi = sh[k][1];
            int curj = sh[k][2];
            int s = sh[k][3]; // 속력
            int d = sh[k][4]; // 방향
            int z = sh[k][0]; // 크기
            int nxti, nxtj;
            if (d == 1) { // 위
                nxtj = curj;
                if (curi - s >= 0) {
                    nxti = curi - s;
                } else {
                    s -= curi;
                    int quo = s / (r - 1);
                    int rem = s % (r - 1);
                    if (quo % 2 == 0) {
                        nxti = rem;
                        sh[k][4] = 2;
                    } else {
                        nxti = r - 1 - rem;
                    }
                }
            } else if (d == 2) { // 아래
                nxtj = curj;
                if (curi + s < r) {
                    nxti = curi + s;
                } else {
                    s -= (r - 1 - curi);
                    int quo = s / (r - 1);
                    int rem = s % (r - 1);
                    if (quo % 2 == 0) {
                        nxti = r - 1 - rem;
                        sh[k][4] = 1;
                    } else {
                        nxti = rem;
                    }
                }
            } else if (d == 3) { // 오른쪽
                nxti = curi;
                if (curj + s < c) {
                    nxtj = curj + s;
                } else {
                    s -= (c - 1 - curj);
                    int quo = s / (c - 1);
                    int rem = s % (c - 1);
                    if (quo % 2 == 0) {
                        nxtj = c - 1 - rem;
                        sh[k][4] = 4;
                    } else {
                        nxtj = rem;
                    }
                }
            } else if (d == 4) { // 왼쪽
                nxti = curi;
                if (curj - s >= 0) {
                    nxtj = curj - s;
                } else {
                    s -= curj;
                    int quo = s / (c - 1);
                    int rem = s % (c - 1);
                    if (quo % 2 == 0) {
                        nxtj = rem;
                        sh[k][4] = 3;
                    } else {
                        nxtj = c - 1 - rem;
                    }
                }
            }
            if (chk[nxti][nxtj] == -1) { // 상어가 없으면
                chk[nxti][nxtj] = k;
            } else { // 있으면 먹고 자신으로 대체
                int idx = chk[nxti][nxtj];
                alive[idx] = false;
                chk[nxti][nxtj] = k;
            }
            if (nxtj == j) {
                if (maxsh == -1) {
                    maxsh = k;
                } else {
                    if (nxti <= sh[maxsh][1]) maxsh = k;
                }
            }
            sh[k][1] = nxti;
            sh[k][2] = nxtj;
        }

        if (maxsh != -1) {
            ans += sh[maxsh][0];
            alive[maxsh] = false;
        }
    }

    cout << ans << '\n';
}