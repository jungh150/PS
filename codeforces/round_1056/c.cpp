#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

bool ispsb(int k) {
    // k는 R의 총 개수
    if (k < 0 || k > n) return false;
    vector<int> dp(n); // dp[i]: i까지 R의 개수
    dp[0] = 1 + k - a[0];
    if (dp[0] < 0 || dp[0] > 1) return false;
    for (int i = 1; i < n; i++) {
        dp[i] = i + 1 + k - dp[i - 1] - a[i];
        if (dp[i] - dp[i - 1] < 0 || dp[i] - dp[i - 1] > 1) return false;
    }
    if (dp[n - 1] != k) return false;
    else return true;
}

void solve() {
    cin >> n;

    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ans = 0;
    if (ispsb(a[0])) ans++;
    if (ispsb(a[0] - 1)) ans++;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}