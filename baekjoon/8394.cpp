#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> dp = vector<int>(n + 1);
    
    dp[0] = 0;
    dp[1] = 1;
    if (n >= 2) {
        dp[2] = 2;
    }

    for (int i = 3; i < n + 1; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10;
    }

    cout << dp[n] << '\n';
}