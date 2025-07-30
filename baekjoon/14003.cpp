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
    a[0] = -1e9 - 1;
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> b;
    b.push_back(a[0]);
    vector<int> dp(n + 1);
    dp[0] = 0;

    for (int i = 1; i < n + 1; i++) {
        if (a[i] > b.back()) {
            b.push_back(a[i]);
            dp[i] = b.size() - 1;
        } else {
            int idx = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            b[idx] = a[i];
            dp[i] = idx;
        }
    }
    
    int maxl = b.size() - 1;
    int tmp = maxl;
    vector<int> ans;
    for (int i = n; i > 0; i--) {
        if (dp[i] == tmp) {
            ans.push_back(a[i]);
            tmp--;
        }
    }
    
    reverse(ans.begin(), ans.end());
    cout << maxl << '\n';
    for (int x: ans) cout << x << ' ';
    cout << '\n';
}