#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, p, q, r, s;
    cin >> n >> p >> q >> r >> s;

    vector<long long> a(n + 1);
    cin >> a[1];

    long long ans = a[1];

    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) a[i] = p * a[i / 2] + q;
        else a[i] = r * a[i / 2] + s;
        ans += a[i];
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