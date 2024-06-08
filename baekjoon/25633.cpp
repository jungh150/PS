#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    int maxa = 0;
    cin >> n;

    // d[i] : i번째 도미노의 무게
    // dp[i] : i번째 도미노까지 봤을 때, 도미노를 i개 사용했을 때 최대 무게
    vector<int> d(n + 1);
    vector<int> dp(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        cin >> d[i];
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j > 0; j--) {
            if (dp[j - 1] >= d[i]) {
                dp[j] = max(dp[j], dp[j - 1] + d[i]);
            }
        }
        dp[1] = max(d[1], d[i]);
    }

    for (int i = n; i > 0; i--) {
        if (dp[i] != 0) {
            cout << i << '\n';
            break;
        }
    }
}