#include <iostream>
using namespace std;

void solve() {
    int x, y, z;
    cin >> x >> y >> z;

    double h = x % 12;
    double m = y;
    double s = z;

    double a = (h + m / 60 + s / 3600) * 360 / 12;
    double b = (m + s / 60) * 360 / 60;
    double c = s * 360 / 60;

    double ans1 = min(abs(a - b), min(a, b) + 360 - max(a, b));
    double ans2 = min(abs(b - c), min(b, c) + 360 - max(b, c));
    double ans3 = min(abs(c - a), min(c, a) + 360 - max(c, a));

    double ans = 1000;
    ans = min(ans, ans1);
    ans = min(ans, ans2);
    ans = min(ans, ans3);

    cout << fixed;
    cout.precision(10);
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