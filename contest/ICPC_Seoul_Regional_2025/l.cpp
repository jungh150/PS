#include <iostream>
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;

    int minl = 1e9;
    int maxl = 0;
    int minr = 1e9;
    int maxr = 0;
    for (int i = 0; i < n; i++) {
        int l, r, y;
        cin >> l >> r >> y;
        minl = min(minl, l);
        maxl = max(maxl, l);
        minr = min(minr, r);
        maxr = max(maxr, r);
    }

    while (q--) {
        int p;
        cin >> p;

        if (maxl <= p && p <= minr) cout << 0 << '\n';
        else if (p <= minl) cout << maxl - p << '\n';
        else if (p >= maxr) cout << p - minr << '\n';
        else if (p <= minr) cout << abs(p - maxl) << '\n';
        else if (p >= maxl) cout << abs(minr - p) << '\n';
        else cout << max(abs(p - minr), abs(p - maxl)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}