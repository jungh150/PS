#include <iostream>
using namespace std;

long long comb(int n, int r) {
    if (r > n) return 0;
    long long ans = 1;
    for (int i = n; i > n - r; i--) {
        ans *= i;
    }
    for (int i = r; i > 0; i--) {
        ans /= i;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, xa, ya, xb, yb;
    cin >> n >> xa >> ya >> xb >> yb;

    long long tans = comb(n + 1, 2);
    long long ans = tans * tans;

    if (xa == xb) {
        if (ya > yb) {
            int tmp = ya;
            ya = yb;
            yb = tmp;
        }
        if (ya < n && yb >= 0) {
            if (ya < 0) ya = -1;
            if (yb > n) yb = n;
            ans += comb(yb - ya, 2) * (n + 1);
        }
    } else if (ya == yb) {
        if (xa > xb) {
            int tmp = xa;
            xa = xb;
            xb = tmp;
        }
        if (xa < n && xb >= 0) {
            if (xa < 0) xa = -1;
            if (xb > n) xb = n;
            ans += comb(xb - xa, 2) * (n + 1);
        }
    }

    cout << ans << '\n';
}