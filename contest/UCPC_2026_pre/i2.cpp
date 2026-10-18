#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i < r; i++)
#define rrep(i, l, r) for(int i = r-1; i >= l; i--)
#define all(x) x.begin(), x.end();
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using cd = complex<double>;

void fastio(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
}

void solve(){
    ll n; cin >> n;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    
    if(n == 1){
        cout << "Yes\n";
        return;
    }
    if(n == 2){
        if(a[0] == a[1]) cout << "Yes\n";
        else cout << "No\n";
        return;
    }
    if(n == 3){
        rep(i, 0, 3000) rep(j, 0, 3000){
            if(a[0] + i != a[2] + j) continue;
            if(a[0] + i != a[1] + i + j) continue;
            cout << "Yes\n";
            return;
        }
        cout << "No\n";
        return;
    }

    int i = 0;
    int j = n - 1;

    while (j - i + 1 > 3) {
        if (a[i] < a[i + 1]) {
            cout << "No\n";
            return;
        } else if (a[i] == a[i + 1]) {
            i += 2;
        } else {
            int dif = a[i] - a[i + 1];
            i++;
            a[i] += dif;
            a[i + 1] += dif;
            i++;
        }

        if (j - i + 1 <= 3) break;

        if (a[j] < a[j - 1]) {
            cout << "No\n";
            return;
        } else if (a[j] == a[j - 1]) {
            j -= 2;
        } else {
            int dif = a[j] - a[j - 1];
            j--;
            a[j] += dif;
            a[j - 1] += dif;
            j--;
        }
    }

    if(j - i + 1 == 0 || j - i + 1 == 1){
        cout << "Yes\n";
        return;
    }
    if(j - i + 1 == 2){
        if(a[i] == a[i + 1]) cout << "Yes\n";
        else cout << "No\n";
        return;
    }
    if(j - i + 1 == 3){
        rep(ii, 0, 3000) rep(jj, 0, 3000){
            if(a[i] + ii != a[i + 2] + jj) continue;
            if(a[i] + ii != a[i + 1] + ii + jj) continue;
            cout << "Yes\n";
            return;
        }
        cout << "No\n";
        return;
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