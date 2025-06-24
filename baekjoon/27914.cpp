#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k, q;
    cin >> n >> k >> q;

    vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<long long> dp(n + 1);
    dp[0] = 0;
    long long sumt = 0;
    long long cur = 0;
    for (int i = 1; i < n + 1; i++) {
        if (a[i] == k) {
            sumt += (cur * (cur + 1) / 2);
            dp[i] = sumt;
            cur = 0;
        } else {
            cur++;
            dp[i] = sumt + (cur * (cur + 1) / 2);
        }
    }

    while (q--) {
        int x;
        cin >> x;
        cout << dp[x] << '\n';
    }
}