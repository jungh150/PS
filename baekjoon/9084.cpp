#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> coin(n);
    for (int i = 0; i < n; i++) cin >> coin[i];

    int m;
    cin >> m;

    // dp[i]: i원을 만들 수 있는 경우의 수
    vector<long long> dp(m + 1, 0);
    dp[0] = 1;

    for (int x: coin) {
        for (int i = x; i < m + 1; i++) {
            dp[i] += dp[i - x];
        }
    }

    cout << dp[m] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}