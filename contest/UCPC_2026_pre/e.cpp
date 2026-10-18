#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i < r; i++)
#define rrep(i, l, r) for(int i = r-1; i >= l; i--)
#define all(x) x.begin(), x.end()
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

struct UnionFind{
    vector<ll> par, cnt;
    vector<ll> minPortCost;
    ll group;
    ll PortCostSum = 0;

    UnionFind(ll N){
        init(N);
    }

    void init(ll N){
        par.resize(N);
        cnt.resize(N);
        minPortCost.resize(N);
        rep(i, 0, N){
            par[i] = i;
            cnt[i] = 1;
        }
        group = N;
        PortCostSum = 0;
    }

    ll find(ll x){
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    bool merge(ll a, ll b){
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(a > b) swap(a, b);
        par[b] = a;
        cnt[a] += cnt[b];
        cnt[b] = 0;
        PortCostSum -= max(minPortCost[a], minPortCost[b]);
        minPortCost[a] = min(minPortCost[a], minPortCost[b]);
        group--;
        return true;
    }
};

void solve(){
    ll N, M; cin >> N >> M;
    vector<array<ll, 3>> roads;
    rep(i, 0, M){
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        roads.push_back({w, u, v});
    }
    sort(all(roads));
    
    UnionFind UF(N);
    rep(i, 0, N) cin >> UF.minPortCost[i];
    rep(i, 0, N) UF.PortCostSum += UF.minPortCost[i];

    ll ans = UF.PortCostSum;
    ll sm = 0;
    for(auto [w, u, v]: roads){
        ll portCost = 0;
        u = UF.find(u);
        v = UF.find(v);
        if(u == v) continue;
        UF.merge(u, v);
        sm += w;
        // cout << u << ' ' << v << ' ' << w << ' ' << sm << ' ' << UF.group << endl;
        if(UF.group == 1){
            ans = min(ans, sm);
            break;
        }
        ans = min(ans, sm + UF.PortCostSum);
    }
    cout << ans;
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