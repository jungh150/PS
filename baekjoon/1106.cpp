#include <iostream>
#include <vector>
using namespace std;

int MAX_COST = 1e5 + 1;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int c, n;
    cin >> c >> n;

    vector<pair<int, int>> a;
    a.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
        int cost, val;
        cin >> cost >> val;
        int cnt = (c + val - 1) / val; // floor(c / val)
        while (cnt--) {
            a.emplace_back(cost, val);
        }
    }

    int an = a.size() - 1;
    vector<vector<int>> dp(MAX_COST, vector<int>(an + 1, 0));

    for (int i = 0; i < MAX_COST; i++) { // i만큼의 비용으로
        for (int j = 1; j < an + 1; j++) { // j번째 아이템까지 확인했을 때
            dp[i][j] = dp[i][j - 1]; // j번째 아이템을 넣지 않은 것이 default
            if (i - a[j].first >= 0) dp[i][j] = max(dp[i][j], dp[i - a[j].first][j - 1] + a[j].second); // j번째 아이템을 넣을 수 있으면 update
        }
    }

    for (int i = 0; i < MAX_COST; i++) {
        if (dp[i][an] >= c) {
            cout << i << '\n';
            return 0;
        }
    }
}