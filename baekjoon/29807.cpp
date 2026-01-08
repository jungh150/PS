#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> a(5, 0);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long ans = 0;

    if (a[0] > a[2]) ans += abs(a[0] - a[2]) * 508;
    else ans += abs(a[0] - a[2]) * 108;

    if (a[1] > a[3]) ans += abs(a[1] - a[3]) * 212;
    else ans += abs(a[1] - a[3]) * 305;

    if (n >= 5) ans += a[4] * 707;

    cout << ans * 4763 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}