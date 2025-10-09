#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> cnt(1001, 0);
    int x = 0;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        string d;
        long long c;
        cin >> d >> c;
        if (c > 1000) ans++;
        else cnt[c]++;
        if (d == "jinju") x = c;
    }

    for (int i = x + 1; i <= 1000; i++) ans += cnt[i];
    cout << x << '\n';
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