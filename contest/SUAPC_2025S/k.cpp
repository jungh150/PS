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
    ll X, N; cin >> X >> N;
    vector<ll> insu;
    for(ll i = 1; i*i <= N; i++){
        if(N%i != 0) continue;
        insu.push_back(i);
        insu.push_back(N/i);
    }
    for(ll i = 1; i*i <= N+1; i++){
        if((N+1)%i != 0) continue;
        insu.push_back(i);
        insu.push_back((N+1)/i);
    }
    set<int> st;
    for(auto a: insu){
        if(a < X) continue;
        // cout << a << ' ' << ((X+2*N)/a - (X-1)/a)%2 << endl;
        // cout << (X+2*N)/a << ' ' << (X-1)/a << endl;
        if(((X+2*N)/a - (X-1)/a)%2) st.insert(a);
    }
    cout << st.size() << '\n';
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