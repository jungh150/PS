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

ll N, H;
vector<pair<ll, bool>> v; // idx, isEnd

void solve(){
    cin >> N >> H;
    rep(i, 0, N){
        int A, B; cin >> A >> B;
        v.push_back({A, false});
        v.push_back({B, true});
    }
    sort(all(v));
    ll cur = 0, cnt = 0;
    vector<ll> v2;
    for(auto [idx, isEnd]: v){
        if(isEnd){
            cur = idx;
            cnt--;
        }
        else{
            if(cnt == 0){
                ll ret = idx - cur - 1;
                // cout << cur << ' ' << idx << ' ' << ret << endl;
                if(ret > 0) v2.push_back(ret);
            }
            cnt++;
        }
    }
    ll ret = H - cur;
    if(ret > 0) v2.push_back(ret);
    sort(all(v2));
    int sz = v2.size();
    // for(auto x: v2) cout << x << ' '; cout << endl;
    // cout << "Sz: " << sz << endl;

    if(sz == 0){
        int Q; cin >> Q;
        while(Q--){
            int T; cin >> T;
            cout << 0 << '\n';
        }
        return;
    }
    
    vector<ll> sf(sz);
    sf[sz-1] = v2[sz-1];
    rrep(i, sz-1, 0) sf[i] = sf[i+1] + v2[i];
    // rep(i, 0, sz) cout << sf[i] << ' '; cout << endl;

    int Q; cin >> Q;
    while(Q--){
        ll T; cin >> T;
        auto idx = lower_bound(all(v2), T) - v2.begin();
        ll cnt = sz - idx;
        // cout << idx << ' ' << cnt << ' ' << sf[idx] << endl;
        cout << sf[idx] - cnt * (T-1) << '\n';
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