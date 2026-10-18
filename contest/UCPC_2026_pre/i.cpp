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
    ll N; cin >> N;
    vector<ll> A(N);
    rep(i, 0, N) cin >> A[i];
    
    if(N == 1){
        cout << "Yes\n";
        return;
    }
    if(N == 2){
        if(A[0] == A[1]) cout << "Yes\n";
        else cout << "No\n";
        return;
    }
    if(N == 3){
        rep(i, 0, 3000) rep(j, 0, 3000){
            if(A[0] + i != A[2] + j) continue;
            if(A[0] + i != A[1] + i + j) continue;
            cout << "Yes\n";
            return;
        }
        cout << "No\n";
        return;
    }
    ll goal = 1e9;
    rep(i, 0, N-3){
        ll more = goal - A[i];
        A[i] += more;
        A[i+1] += more;
    }
    {
        ll more = goal - A[N-1];
        A[N-1] += more;
        A[N-2] += more;
    }
    if(A[N-3] == A[N-2]) cout << "Yes\n";
    else cout << "No\n";
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