#include <iostream>
#include <vector>
using namespace std;

// vector<vector<int>> dp;
int dp[5 * 1000][5 * 1000];

void solve() {
    int n;
    cin >> n;
    // dp = vector<vector<int>>(5 * 10000 + 1, vector<int>(5 * 10000 + 1, 0));
    // cout << dp[50000][50000] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}