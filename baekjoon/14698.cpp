#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

int mod = 1e9 + 7;

void solve() {
    ll ans = 1;

    int n;
    cin >> n;
    priority_queue<ll, vector<ll>, greater<ll>> q;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        q.push(x);
    }

    while (q.size() >= 2) {
        ll x = q.top();
        q.pop();
        ll y = q.top();
        q.pop();
        ll tmp = x * y;

        q.push(tmp);
        tmp %= mod;
        ans *= tmp;
        ans %= mod;
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