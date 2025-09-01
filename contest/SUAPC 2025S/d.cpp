/*###################################################
##           Author: Jiho Kim (wlgh7407)           ##
###################################################*/

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("bmi2","adx","avx2")
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i < r; i++)
#define rrep(i, r, l) for(int i = r-1; i >= l; i--)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


void fastio(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
}

void solve(){
    ll n, a, b, c;
    cin >> n >> a >> b >> c;

    ll tmp1 = n * (a * b * c - a * b - b * c - c * a);
    ll tmp2 = a * b + b * c + c * a;

    if (tmp1 < 0) {
        cout << -1 << '\n';
        return;
    }
    if (tmp1 % tmp2 != 0) {
        cout << -1 << '\n';
        return;
    }

    ll k = tmp1 / tmp2;
    if (((n + k) % a == 0) && ((n + k) % b == 0) && ((n + k) % c == 0)) {
        cout << k << '\n';
    } else {
        cout << -1 << '\n';
    }
}

int main(){
    fastio();
    int tc = 1;
    cin >> tc;
    rep(TC, 1, tc+1){
        solve();
    }
    return 0;
}