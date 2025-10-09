#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    int x = 0;

    for (int i = 0; i < n; i++) {
        string d;
        int c;
        cin >> d >> c;
        a[i] = c;
        if (d == "jinju") x = c;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > x) ans++;
    }

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