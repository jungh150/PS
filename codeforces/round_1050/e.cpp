#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    if (n % k != 0) {
        cout << 0 << '\n';
        return;
    }

    // cout << "n\n";
    // cout << n << '\n';

    // cout << "cnt (before div)\n";
    // for (int x: cnt) cout << x << ' ';
    // cout << '\n';

    for (int i = 0; i < n + 1; i++) {
        if (cnt[i] % k != 0) {
            cout << 0 << '\n';
            return;
        }
        cnt[i] = (cnt[i] / k);
    }

    // cout << "cnt (after div)\n";
    // for (int x: cnt) cout << x << ' ';
    // cout << '\n';

    vector<int> cur(n + 1, 0);
    int l = 0;
    int r = 0;
    long long ans = 0;
    for (r = 0; r < n; r++) {
        cur[a[r]]++;
        while (cur[a[r]] > cnt[a[r]]) {
            cur[a[l]]--;
            l++;
        }
        ans += (r - l + 1);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}