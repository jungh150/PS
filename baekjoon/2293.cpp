#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<long long> dp(k + 1, 0);
    dp[0] = 1;

    while (n--) {
        int x;
        cin >> x;
        for (int i = x; i <= k; i++) {
            dp[i] += dp[i - x];
        }
    }

    cout << dp[k] << '\n';
}