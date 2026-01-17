#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll pow(ll a, ll b) {
    if (b == 1) return a;
    ll tmp = pow(a, b / 2);
    if (b % 2 == 0) return tmp * tmp;
    else return (tmp * tmp) * a;
}

void solve() {
    ll k = 5 * 1e6;
    vector<ll> a;

    while (1) {
        ll x;
        cin >> x;
        if (x == 0) break;
        a.push_back(x);
    }

    int n = a.size();
    sort(a.begin(), a.end(), greater<>());

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > k) {
            cout << "Too expensive\n";
            return;
        }
        ans += 2 * pow(a[i], i + 1);
        if (ans > k) {
            cout << "Too expensive\n";
            return;
        }
    }

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