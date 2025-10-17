#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<int> ps(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        ps[i] = ps[i - 1] + a[i];
    }

    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j < n + 1; j++) {
            ans = max(ans, (ps[j] - ps[i - 1]) / (j - i + 1));
        }
    }

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