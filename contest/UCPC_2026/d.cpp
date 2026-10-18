#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i < r; i++)
#define rrep(i, l, r) for(int i = r-1; i >= l; i--)
#define all(x) x.begin(), x.end()
#define int long long
using namespace std;
using ll = long long;

void fastio(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
}


const ll MOD = 998244353;
template<ll mod = MOD>
struct ModInt {
    ll val;

    ModInt() : val(0) {}
    ModInt(ll x) : val(x%mod) {if(val < 0) val += mod;}

    ModInt& operator+=(const ModInt& a){ val += a.val; if(val >= mod) val -= mod; return *this; }
    ModInt& operator-=(const ModInt& a){ val -= a.val; if(val < 0) val += mod; return *this; }
    ModInt& operator*=(const ModInt& a){ val = val * a.val % mod; return *this; }
    ModInt& operator%=(const ModInt& a){ if(a) val %= a.val; return *this; }

    ModInt operator+(const ModInt& a) const{ModInt res = *this; return res += a;}
    ModInt operator-(const ModInt& a) const{ModInt res = *this; return res -= a;}
    ModInt operator*(const ModInt& a) const{ModInt res = *this; return res *= a;}
    ModInt operator%(const ModInt& a) const{ModInt res = *this; return res %= a;}

    ModInt& operator++(){val++; if(val == mod) val = 0; return *this;}
    ModInt& operator--(){val--; if(val == -1) val = mod-1; return *this;}

    friend ostream& operator<<(ostream& os, const ModInt& a){return os << a.val;}
    friend istream& operator>>(istream& is, ModInt& a){return is >> a.val;}

    bool operator==(const ModInt& a) const{return val == a.val;}
    bool operator!=(const ModInt& a) const{return val != a.val;}

    const ll& operator*() const{return val;}
    ll& operator*(){return val;}

    ModInt pow(ll n) const{
        ModInt a = *this, res = 1;
        while(n){
            if(n&1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

    ModInt inv() const{
        return pow(mod-2);
    }

    ModInt operator/(const ModInt& a) const{ return *this * a.inv(); }
    ModInt& operator/=(const ModInt& a) { return *this *= a.inv(); }
};
using mint = ModInt<MOD>;

int N;
vector<int> links[202020];
mint depth[202020];
mint sub_cnt[202020];
mint ans[202020];

void dfs(int cur, int par, int dep){
    sub_cnt[cur] = mint(1);
    depth[cur] = mint(dep);
    for(auto nxt: links[cur]){
        if(par == nxt) continue;
        dfs(nxt, cur, dep+1);
        sub_cnt[cur] += sub_cnt[nxt];
    }
}

void dfs2(int cur, int par, mint weight){
    assert(0 <= weight.val && weight.val < 998244353);
    ans[cur] = weight + depth[cur];
    for(auto nxt: links[cur]){
        if(nxt == par) continue;
        mint tmp = sub_cnt[cur];
        tmp -= sub_cnt[nxt];
        tmp -= mint(1);
        tmp *= mint(2).inv();
        dfs2(nxt, cur, weight + tmp);
    }
}

void solve(){
    cin >> N;
    rep(i, 0, N-1){
        int u, v; cin >> u >> v;
        u--; v--;
        links[u].push_back(v);
        links[v].push_back(u);
    }

    rep(i, 0, N){
        depth[i] = 0;
        sub_cnt[i] = 0;
        ans[i] = 0;
    }

    dfs(0, -1, 1);
    dfs2(0, -1, 0);

    rep(i, 0, N) cout << ans[i].val << '\n';
}

signed main(){
    fastio();
    int tc = 1;
    // cin >> tc;
    rep(TC, 1, tc+1){
        solve();
    }
    return 0;
}