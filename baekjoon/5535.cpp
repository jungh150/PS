#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int d, n;
    cin >> d >> n;

    vector<int> tem(d + 1);
    vector<vector<int>> clo(n + 1, vector<int>(3));

    for (int i = 1; i < d + 1; i++) cin >> tem[i];
    for (int i = 1; i < n + 1; i++) cin >> clo[i][0] >> clo[i][1] >> clo[i][2];

    vector<vector<pair<int, int>>> dp(d + 1, vector<pair<int, int>>(2));
    // dp[i][0] = i번째 날까지 봤을 때 {옷의 화려함의 최소, 그 때까지의 합}
    // dp[i][1] = i번째 날까지 봤을 때 {옷의 화려함의 최대, 그 때까지의 합}

    int minc = 1000;
    int maxc = 0;

    for (int i = 1; i < n + 1; i++) {
        if (tem[1] >= clo[i][0] && tem[1] <= clo[i][1]) {
            minc = min(minc, clo[i][2]);
            maxc = max(maxc, clo[i][2]);
        }
    }
    dp[1][0] = {minc, 0};
    dp[1][1] = {maxc, 0};

    for (int i = 2; i < d + 1; i++) {
        minc = 1000;
        maxc = 0;
        for (int j = 1; j < n + 1; j++) {
            if (tem[i] >= clo[j][0] && tem[i] <= clo[j][1]) {
                minc = min(minc, clo[j][2]);
                maxc = max(maxc, clo[j][2]);
            }
        }
        dp[i][0].first = minc;
        dp[i][0].second = max(dp[i - 1][0].second + abs(minc - dp[i - 1][0].first), dp[i - 1][1].second + abs(minc - dp[i - 1][1].first));
        dp[i][1].first = maxc;
        dp[i][1].second = max(dp[i - 1][0].second + abs(maxc - dp[i - 1][0].first), dp[i - 1][1].second + abs(maxc - dp[i - 1][1].first));
    }

    cout << max(dp[d][0].second, dp[d][1].second) << '\n';
}