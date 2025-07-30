#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> dp(n + 1, 0);
    int maxa = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
        maxa = max(maxa, dp[i]);
    }

    int tmp = maxa;
    vector<int> ans;
    for (int i = n; i > 0; i--) {
        if (dp[i] == tmp) {
            ans.push_back(a[i]);
            tmp--;
        }
    }

    reverse(ans.begin(), ans.end());
    cout << maxa << '\n';
    for (int x: ans) cout << x << ' ';
    cout << '\n';
}