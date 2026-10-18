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

    ModInt inv() const{ // mod must be prime
        return pow(mod-2);
    }

    ModInt operator/(const ModInt& a) const{ return *this * a.inv(); }
    ModInt& operator/=(const ModInt& a) { return *this *= a.inv(); }
};
using mint = ModInt<MOD>;

struct SegmentTreeSum{
    vector<mint> tree;
    ll sz;

    SegmentTreeSum(ll N, vector<mint> a = vector<mint>()){
        sz = 1;
        while(sz < N) sz <<= 1;
        tree.resize(2*sz, mint(0));
        if(a.size() > 0){
            assert(a.size() == N);
            rep(i, 0, N) tree[sz+i] = a[i];
            rrep(i, 1, sz) tree[i] = pull(tree[i<<1], tree[i<<1|1]);
        }
    };

    mint pull(mint a, mint b){
        return a+b;
    }

    void add(ll i, mint x){
        ll idx = sz + i;
        tree[idx] = x;
        while(idx >>= 1) tree[idx] = pull(tree[idx<<1], tree[idx<<1|1]);
    }

    void set(ll i, mint x){
        ll idx = sz + i;
        tree[idx] = x;
        while(idx >>= 1) tree[idx] = pull(tree[idx<<1], tree[idx<<1|1]);
    }

    mint query(ll L, ll R){
        ll left = L + sz, right = R + sz;
        mint ret = 0;
        while(left <= right){
            if((left&1)==1) ret = pull(ret, tree[left++]);
            if((right&1)==0) ret = pull(ret, tree[right--]);
            left >>= 1; right >>= 1;
        }
        return ret;
    }
};

vector<mint> fact(200010), invFact(200010);

mint nCr(ll N, ll R){
    return fact[N]*invFact[N-R]*invFact[R];
}

void solve(){
    ll N; cin >> N;
    vector<ll> P(N);
    rep(i, 0, N) cin >> P[i];

    vector<mint> cnt(N+1, mint(0));
    cnt[1] = mint(N);
    vector<mint> DP(N, mint(1));
    rep(n, 2, N+1){
        vector<mint> nDP(N);
        SegmentTreeSum ST(N+1);
        rep(i, 0, N){
            nDP[i] = ST.query(0, P[i]-1);
            cnt[n] += nDP[i];
            ST.set(P[i], mint(DP[i]));
        }
        swap(DP, nDP);
    }

    fact[0] = mint(1);
    rep(i, 1, N+1) fact[i] = fact[i-1] * mint(i);
    invFact[N] = fact[N].inv();
    rrep(i, 0, N+1) invFact[i-1] = invFact[i]*mint(i);

    mint ans(0);
    rep(i, 1, N+1) ans += mint(1) - cnt[i] / nCr(N, i);
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