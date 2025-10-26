#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<vector<int>> adp(n, vector<int>(n));
    vector<vector<int>> bdp(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        int minidx = i;
        for (int j = i; j < n; j++) {
            adp[i][j] = minidx;
            if (a[j] < a[minidx]) {
                minidx = j;
                adp[i][j] = minidx;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int minidx = i;
        for (int j = i; j < n; j++) {
            bdp[i][j] = minidx;
            if (b[j] < b[minidx]) {
                minidx = j;
                bdp[i][j] = minidx;
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << adp[i][j] << ' ';
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << bdp[i][j] << ' ';
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    int ans = 0;
    int s = 0;
    while (s < n) {
        for (int e = n - 1; e >= 0; e--) {
            if (adp[s][e] == bdp[s][e]) {
                s = e + 1;
                ans++;
                break;
            }
        }
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