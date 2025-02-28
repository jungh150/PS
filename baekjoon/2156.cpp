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
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = a[1];
    if (n > 1) dp[2] = a[1] + a[2];

    for (int i = 3; i < n + 1; i++) {
        dp[i] = max(max(dp[i - 1], dp[i - 2] + a[i]), dp[i - 3] + a[i - 1] + a[i]);
    }

    cout << dp[n] << '\n';
}