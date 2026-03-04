#include <iostream>
using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;

    ll a = 0;
    ll b = 0;

    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a -= x;
        b -= y;
    }

    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a += x;
        b += y;
    }

    cout << a / n << ' ' << b / n << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}