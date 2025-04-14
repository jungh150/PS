#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> d(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> d[i];

    // d가 홀수개이면 바로 종료
    if (n % 2 == 1) {
        cout << "NO\n";
        return 0;
    }

    // dp[i][j][k]: i번째 축까지 사용했고 짝수번째로 사용한 축이 j개일 때 상태 k(0~359)가 가능한지
    //              가능하다면 이전 상태(이전 j) 저장, 불가능하다면 -1 저장 (j만 저장해도 이전 상태를 추척할 수 있음)
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n / 2 + 1, vector<int>(360, -1)));

    dp[0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            for (int k = 0; k < 360; k++) {
                if (dp[i][j][k] != -1) { // 가능한 상태라면
                    dp[i + 1][j][(k - 2 * d[i + 1] + 360) % 360] = j;
                    dp[i + 1][j + 1][(k + 2 * d[i + 1] + 360) % 360] = j;
                }
            }
        }
    }

    if (dp[n][n / 2][0] != -1) { // 마지막에 원상태로 돌아올 수 있다면
        vector<int> even;
        vector<int> odd;

        int ci = n;
        int cj = n / 2;
        int ck = 0;
        while (ci > 0) {
            int pj = dp[ci][cj][ck];
            if (cj == pj + 1) { // ci번째 축이 짝수번째로 사용되었으면
                even.push_back(ci);
                ck = (ck - 2 * d[ci] + 360) % 360;
            } else if (cj == pj) { // ci번째 축이 홀수번째로 사용되었으면
                odd.push_back(ci);
                ck = (ck + 2 * d[ci] + 360) % 360;
            }
            ci--;
            cj = pj;
        }

        cout << "YES\n";
        int tmpn = n / 2;
        for (int i = 0; i < tmpn; i++) cout << even[i] << ' ' << odd[i] << ' ';
        cout << '\n';
    } else { // 불가능하다면
        cout << "NO\n";
    }
}