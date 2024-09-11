#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> dp(n + 1, 100);

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 1; i < 300; i++) {
        int sq = i * i;
        int idx = sq;
        while (idx < n + 1) {
            dp[idx] = min(dp[idx - sq] + 1, dp[idx]);
            idx++;
        }
    }

    cout << dp[n] << '\n';
}