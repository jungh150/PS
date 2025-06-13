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
    for (int i = 0; i < n; i++) {
        int cost, val;
        cin >> cost >> val;
        int cnt = (c + val - 1) / val; // floor(c / val)
        while (cnt--) {
            a.emplace_back(cost, val);
        }
    }

    int an = a.size();
    vector<int> dp(MAX_COST, 0);

    for (int i = 0; i < an; i++) { // i번째 아이템 확인
        for (int j = MAX_COST - 1; j >= 0; j--) { // j만큼의 비용 (역방향으로 update)
            if (j - a[i].first >= 0) dp[j] = max(dp[j], dp[j - a[i].first] + a[i].second);
        }
    }

    for (int i = 0; i < MAX_COST; i++) {
        if (dp[i] >= c) {
            cout << i << '\n';
            return 0;
        }
    }
}