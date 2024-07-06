#include <iostream>
#include <vector>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, l, w, h;
    cin >> n >> l >> w >> h;

    ld li = 0;
    ld ri = l + 1;
    for (int i = 0; i < 100; i++) {
        ld mi = (li + ri) / 2;
        ll tmp = ((ll) (l / mi) * (ll) (w / mi) * (ll) (h / mi));
        if (tmp < n) ri = mi;
        else li = mi;
    }

    cout << fixed;
    cout.precision(10);
    cout << li << '\n';
}