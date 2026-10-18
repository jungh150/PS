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
    cout << "? 1013" << endl;
    string S; cin >> S;
    if(S == "SUAPC!"){
        cout << "! 1013" << endl;
        return;
    }
    if(S == "Hot"){
        rep(i, 0, 7){
            cout << "? 506" << endl;
            cin >> S;
        }
        cout << "? 508" << endl;
        cin >> S;
        if(S == "Hot") cout << "! 507" << endl;
        else cout << "! 508" << endl;
    }
    else{
        rep(i, 0, 7){
            cout << "? 1520" << endl;
            cin >> S;
        }
        cout << "? 1518" << endl;
        cin >> S;
        if(S == "Hot") cout << "! 1517" << endl;
        else cout << "! 1518" << endl;
    }
}

int main(){
    fastio();
    int tc = 1;
    // cin >> tc;
    rep(TC, 1, tc+1){
        solve();
    }
    return 0;
}