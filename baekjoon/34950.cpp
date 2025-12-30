#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

vector<ll> ans;

void f(ll n, ll l, ll r) {
    if (n == 0) return;
    if (r - l + 1 == n) {
        for (ll i = l; i <= r; i++) ans.push_back(i);
    } else {
        ll m = (l + r) / 2;
        ll newn = n / 2;
        f(newn, l, m - 1);
        f(n - newn, m + 1, r);
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;

    f(n, 0, k);

    for (ll x: ans) cout << x << ' ';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}