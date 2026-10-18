#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, d;
    cin >> n >> d;

    vector<vector<int>> a(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    sort(a.begin(), a.end());

    int ans = 0;
    for (int k = 0; k < n; k++) {
        if (a[k][0] > d) break;
        ans = max(ans, a[k][1] + a[k][2]);
    }

    int i = 0;
    int max1 = 0;
    int max2 = 0;

    for (int j = n - 1; j >= 0; j--) {
        while (i + 1 < n && a[i + 1][0] + a[j][0] <= d) {
            i++;
            max1 = max(max1, a[i][1]);
            max2 = max(max2, a[i][2]);
        }
        ans = max(ans, max(max1 + a[j][2], max2 + a[j][1]));
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}