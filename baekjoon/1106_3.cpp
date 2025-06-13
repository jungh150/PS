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

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    vector<int> dp(MAX_COST, 0);

    for (int i = 0; i < n; i++) { // i번째 아이템 확인
        for (int j = 0; j < MAX_COST; j++) { // j만큼의 비용 (정방향으로 update)
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