#include <iostream>
using namespace std;

typedef long long ll;

int ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll res = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);
    if (res > 0) return 1;
    else if (res < 0) return -1;
    else return 0;
}

void crossp(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) {
    double px = (double) ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    double py = (double) ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    cout << fixed;
    cout.precision(12);
    cout << px << ' ' << py << '\n';
}

void solve() {
    ll x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    int ccw1 = ccw(x1, y1, x2, y2, x3, y3);
    int ccw2 = ccw(x1, y1, x2, y2, x4, y4);
    int ccw3 = ccw(x3, y3, x4, y4, x1, y1);
    int ccw4 = ccw(x3, y3, x4, y4, x2, y2);

    if (ccw1 == 0 && ccw2 == 0 && ccw3 == 0 && ccw4 == 0) { // 전부 다 한 직선 위에 있는 경우
        if (min(x1, x2) <= max(x3, x4) && min(x3, x4) <= max(x1, x2) && min(y1, y2) <= max(y3, y4) && min(y3, y4) <= max(y1, y2)) {
            cout << 1 << '\n';
            if (min(x1, x2) == max(x3, x4) && min(y1, y2) == max(y3, y4)) cout << min(x1, x2) << ' ' << min(y1, y2) << '\n';
            else if (min(x1, x2) == max(x3, x4) && max(y1, y2) == min(y3, y4)) cout << min(x1, x2) << ' ' << max(y1, y2) << '\n';
            else if (max(x1, x2) == min(x3, x4) && min(y1, y2) == max(y3, y4)) cout << max(x1, x2) << ' ' << min(y1, y2) << '\n';
            else if (max(x1, x2) == min(x3, x4) && max(y1, y2) == min(y3, y4)) cout << max(x1, x2) << ' ' << max(y1, y2) << '\n';
        } else {
            cout << 0 << '\n';
        }
    } else {
        if (ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0) {
            cout << 1 << '\n';
            crossp(x1, y1, x2, y2, x3, y3, x4, y4);
        } else {
            cout << 0 << '\n';
        }
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