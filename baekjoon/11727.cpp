#include <iostream>
#include <vector>
using namespace std;

int mod = 10007;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> dp(n + 1, 0);

    dp[1] = 1;
    if (n > 1) dp[2] = 3;
    for (int i = 3; i <= n; i++) {
        dp[i] = (2 * dp[i - 2] + dp[i - 1]) % mod;
    }

    cout << dp[n] << '\n';
}