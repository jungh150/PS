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

int N;
string S;
vector<int> v;

void solve(){
    cin >> N;
    cin >> S;
    int cnt = 0;
    for(auto c: S){
        if(c == 'H') cnt++;
        else if(cnt != 0){
            v.push_back(cnt);
            cnt = 0;
        }
    }
    if(cnt != 0) v.push_back(cnt);

    bool flag = false;
    for(auto a: v){
        if(a == 3) flag = true;
        if(a >= 5) flag = true;
    }
    if(flag){
        cout << "First";
        return;
    }
    int ccnt = 0;
    for(auto a: v){
        if(a == 4) ccnt += 3;
        else ccnt += a;
    }
    if(ccnt%2) cout << "First";
    else cout << "Second";
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