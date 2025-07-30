#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n, l, k;
    cin >> n >> l >> k;

    vector<vector<long long>> dp(n + 1, vector<long long>(l + 1, 0));
    // dp[i][j]: 길이가 i이고 1의 개수가 j개인 이진수의 개수

    dp[0][0] = 1;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < l + 1; j++) {
            dp[i][j] = dp[i - 1][j]; // 0 추가
            if (j > 0) dp[i][j] += dp[i - 1][j - 1]; // 1 추가
        }
    }

    for (int i = 1; i < n + 1; i++) { // i: 현재 확정하려는 자리
        long long sumt = 0;
        for (int j = 0; j <= l; j++) sumt += dp[n - i][j];

        if (sumt >= k) {
            cout << 0;
        } else {
            cout << 1;
            k -= sumt;
            l--;
        }
    }
    cout << '\n';
}