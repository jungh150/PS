#include <iostream>
using namespace std;

typedef long long ll;

int ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll res = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}

void solve() {
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    int ccw1 = ccw(x1, y1, x2, y2, x3, y3) * ccw(x1, y1, x2, y2, x4, y4);
    int ccw2 = ccw(x3, y3, x4, y4, x1, y1) * ccw(x3, y3, x4, y4, x2, y2);

    if (ccw1 == 0 && ccw2 == 0) {
        if (min(x1, x2) <= max(x3, x4) && min(x3, x4) <= max(x1, x2) && min(y1, y2) <= max(y3, y4) && min(y3, y4) <= max(y1, y2)) cout << 1 << '\n';
        else cout << 0 << '\n';
    } else {
        if (ccw1 <= 0 && ccw2 <= 0) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}