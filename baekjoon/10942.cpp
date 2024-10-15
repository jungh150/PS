#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n;

    vector<int> a(n);
    vector<vector<bool>> dp(n, vector<bool>(n, 0));

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i][i] = 1;
        if (i == 0) continue;
        if (a[i] == a[i - 1]) dp[i - 1][i] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j + i < n - 1; j++) {
            if (dp[j][j + i] && a[j - 1] == a[j + i + 1]) dp[j - 1][j + i + 1] = 1;
        }
    }

    cin >> m;
    while (m--) {
        int s, e;
        cin >> s >> e;
        cout << dp[s - 1][e - 1] << '\n';
    }
}