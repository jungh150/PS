#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> dp(n + 1, 0);
    int maxa = 0;
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + a[i]);
        }
        maxa = max(maxa, dp[i]);
    }

    cout << maxa << '\n';
}