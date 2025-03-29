#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> dp(n, 0);

    for (int i = 0; i < n; i++) cin >> a[i];

    int maxa = 0;
    for (int i = 0; i < n; i++) {
        int maxt = 0;
        for (int j = 0; j < i; j++) {
            if (a[i] < a[j]) maxt = max(maxt, dp[j]);
        }
        dp[i] = maxt + 1;
        maxa = max(maxa, dp[i]);
    }

    cout << maxa << '\n';
}