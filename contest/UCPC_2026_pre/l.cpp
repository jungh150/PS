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

void fastio(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
}

void solve(){
    mint a(6);
    mint b(1);
    cout << a * b.inv() << '\n';
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