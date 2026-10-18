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


struct LazySegmentTree{
    vector<ll> tree, lazy;
    ll sz;

    void init(ll n){
        sz = 1;
        while(sz < n) sz <<= 1;
        tree.assign(sz<<1, 0);
        lazy.assign(sz<<1, 0);
    }

    void set(ll idx, ll val){ tree[sz|idx] = val; }
    void build(){
        for(ll i = sz-1; i > 0; i--) tree[i] = tree[i<<1] + tree[i<<1|1];
    }

    void propagate(ll node, ll start, ll end){
        if(lazy[node] != 0){
            tree[node] = (end - start + 1) - tree[node];
            if(start != end){
                lazy[node<<1] ^= lazy[node];
                lazy[node<<1|1] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(ll left, ll right, ll diff){
        update(1, 0, sz-1, left, right, diff);
        return;
    }

    void update(ll node, ll start, ll end, ll left, ll right, ll diff){
        propagate(node, start, end);
        if(left > end || right < start) return;
        if(left <= start && end <= right){
            tree[node] = (end - start + 1) - tree[node];
            if(start != end){
                lazy[node<<1] ^= diff;
                lazy[node<<1|1] ^= diff;
            }
            return;
        }
        ll mid = (start + end)>>1;
        update(node<<1, start, mid, left, right, diff);
        update(node<<1|1, mid+1, end, left, right, diff);
        tree[node] = tree[node<<1] + tree[node<<1|1];
        return;
    }

    ll query(ll left, ll right){
        return query(1, 0, sz-1, left, right);
    }

    ll query(ll node, ll start, ll end, ll left, ll right){
        propagate(node, start, end);
        if(left > end || right < start) return 0;
        if(left <= start && end <= right) return tree[node];
        ll mid = (start + end)>>1;
        return query(node<<1, start, mid, left, right) + query(node<<1|1, mid+1, end, left, right);
    }
}LST;

int N, Q;
string S;

bool check(int i){
    if(i < 0) return false;
    if(i >= N-2) return false;
    // cout << "check " << i << endl;
    int ret1 = LST.query(i, i);
    int ret2 = LST.query(i+1, i+1);
    int ret3 = LST.query(i+2, i+2);
    if(ret1 != ret2 && ret2 != ret3) return true;
    return false;
}

void solve(){
    cin >> N;
    cin >> S;
    LST.init(N);
    rep(i, 0, N) if(S[i] == '>') LST.set(i, 1);
    int ans = 0;
    rep(i, 0, N-2){
        bool flag1 = (S[i] != S[i+1]);
        bool flag2 = (S[i+1] != S[i+2]);
        if(flag1 && flag2) ans++;
    }
    cin >> Q;
    while(Q--){
        int op; cin >> op;
        if(op == 1){
            int a, b; cin >> a >> b;
            a--; b--;
            set<int> st;
            st.insert(a-2);
            st.insert(a-1);
            st.insert(b-1);
            st.insert(b);
            for(auto x: st) if(check(x)) ans--;
            LST.update(a, b, 1);
            for(auto x: st) if(check(x)) ans++;
        }
        else cout << ans << '\n';

        // rep(i, 0, N) cout << LST.query(i, i);
        // cout << "ans: " << ans << endl;
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