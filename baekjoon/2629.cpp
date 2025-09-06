#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    int m = 40000; // 구슬의 최대 무게

    // dp[i][j]: i번째 추까지 확인했을 때, 무게 차가 j가 되는 것이 가능한지
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            if (!dp[i - 1][j]) continue;
            dp[i][j] = 1;
            if (j + a[i] < m + 1) dp[i][j + a[i]] = 1;
            if (abs(j - a[i]) < m + 1) dp[i][abs(j - a[i])] = 1;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (dp[n][x]) cout << "Y ";
        else cout << "N ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}