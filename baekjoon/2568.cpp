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

    vector<pair<int, int>> a(n + 1);
    a[0].first = a[1].first = 0;
    for (int i = 1; i < n + 1; i++) cin >> a[i].first >> a[i].second;

    sort(a.begin(), a.end());

    vector<int> b;
    int maxi = 0;
    b.push_back(a[0].second);
    vector<int> dp(n + 1);

    for (int i = 1; i < n + 1; i++) {
        if (a[i].second > b[maxi]) {
            maxi++;
            b.push_back(a[i].second);
            dp[i] = maxi;
        } else {
            int idx = lower_bound(b.begin(), b.end(), a[i].second) - b.begin();
            b[idx] = a[i].second;
            dp[i] = idx;
        }
    }

    cout << n - maxi << '\n';

    vector<int> ans(maxi + 1);
    for (int i = n; i > 0; i--) {
        if (dp[i] == maxi) {
            ans[maxi] = a[i].first;
            maxi--;
        }
    }

    int idx = 1;
    for (int i = 1; i < n + 1; i++) {
        if (a[i].first == ans[idx]) idx++;
        else cout << a[i].first << '\n';
    }
}