#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    vector<int> dp(n + 1, 0);
    for (int i = 2; i < n + 1; i++) {
        for (int j = 1; j < i / 2 + 1; j++) {
            dp[i] = max(dp[i], dp[j] + dp[i - j] + j * (i - j));
        }
    }

    cout << dp[n] << '\n';
}