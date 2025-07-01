#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> dp(n + 1);
    dp[0] = 0;

    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        dp[i] = dp[i - 1] + a[i];
    }

    int mint = 1e9;
    int ans = -1e9;
    for (int i = 0; i < n; i++) {
        mint = min(mint, dp[i]);
        ans = max(ans, dp[i + 1] - mint);
    }

    cout << ans << '\n';
}