#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i < r; i++)
#define rrep(i, l, r) for(int i = r-1; i >= l; i--)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

void fastio(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
}

void solve(){
    int N; cin >> N;
    string S; cin >> S;
    int L = 0, R = 3*N-1;

    string T = "";
    rep(i, 0, N) T += "BLD";
    rep(i, 0, 3*N-1){
        char x = S[i];
        if(x != T[L] && x != T[R]){
            cout << "No";
            return;
        }
        else if(x != T[L] && x == T[R]) R--;
        else if(x == T[L] && x != T[R]) L++;
        else{
            if(S[i+1] == T[L+1]) L++;
            else R--;
        }
    }
    cout << "Yes";
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