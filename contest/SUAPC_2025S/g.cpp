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

ll N;
ll X[4040];

ll par[4040], cnt[4040];

int popcnt(ll A){
    int ret = 0;
    while(A){
        if(A%2) ret++;
        A >>= 1;
    }
    return ret;
}

ll find(ll x){
    if(x == par[x]) return x;
    return par[x] = find(par[x]);
}

bool merge(ll a, ll b){
    a = find(a);
    b = find(b);
    if(a == b) return false;
    if(a > b) swap(a, b); // now a < b
    cnt[a] += cnt[b];
    par[b] = a;
    return true;
}

bool DP[4040][4040];

void solve(){
    cin >> N; N *= 2;
    rep(i, 0, N){
        par[i] = i;
        cnt[i] = 1;
    }
    rep(i, 0, N) cin >> X[i];
    rep(i, 0, N) rep(j, i+1, N){
        ll ret = X[i] ^ X[j];
        if(popcnt(ret) == 1){
            merge(i, j);
        }
    }
    vector<int> bags, idxs;
    rep(i, 0, N) if(i == par[i]){
        bags.push_back(cnt[i]);
        idxs.push_back(i);
    }
    DP[0][0] = true;
    rep(i, 0, bags.size()){
        int sz = bags[i];
        rep(j, 0, N){
            if(!DP[i][j]) continue;
            DP[i+1][j] = true;
            DP[i+1][j+sz] = true;
        }
    }

    
    int sz = bags.size();

    if(!DP[sz][N/2]){
        cout << -1;
        return;
    }
    
    // for(auto s: bags) cout << s << ' '; cout << endl;
    // rep(i, 0, sz+1){
    //     rep(j, 0, N+1) cout << DP[i][j] << ' ';
    //     cout << endl;
    // }

    set<int> used;
    int cx = sz, cy = N/2;
    while(1){
        if(cx == 0 || cy == 0) break;
        if(DP[cx-1][cy]) cx--;
        else{
            used.insert(idxs[cx-1]);
            cx--;
            cy -= bags[cx];
        }
    }
    // for(auto a: used) cout << a << ' '; cout << endl;

    // rep(i, 0, N) cout << find(par[i]) << ' '; cout << endl;

    rep(i, 0, N) if(used.count(find(par[i]))) cout << X[i] << ' '; cout << endl;
    rep(i, 0, N) if(!used.count(find(par[i]))) cout << X[i] << ' ';
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