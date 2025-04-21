#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> mem(n);
    for (int i = 0; i < n; i++) cin >> mem[i];

    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    vector<int> dp(10001, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 10000; j >= 0; j--) { // 역순!
            if (j - c[i] >= 0) dp[j] = max(dp[j], dp[j - c[i]] + mem[i]);
        }
    }

    for (int i = 0; i < 10001; i++) {
        if (dp[i] >= m) {
            cout << i << '\n';
            return 0;
        }
    }
}