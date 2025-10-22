#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    long long ans = 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<long long> ps(n);
    ps[0] = a[0];
    for (int i = 1; i < n; i++) ps[i] = ps[i - 1] + a[i];

    sort(ps.begin(), ps.end(), greater<>());
    for (int i = 0; i < k; i++) ans += ps[i];

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