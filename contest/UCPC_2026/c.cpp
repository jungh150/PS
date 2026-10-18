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
    string S; cin >> S;
    int N = S.size();
    S = "$" + S;
    vector<int> inside(N+1), fromside(N+1), possidx(N+1);
    inside[0] = 10000;
    vector<int> v;
    v.push_back(0);

    vector<vector<int>> poss(130);

    rep(i, 1, N+1){
        char x = S[i];
        if('A' <= x && x <= 'Z') v.push_back(i);
        else{
            int last = v[v.size()-1];
            if(last == 0){
                cout << -1;
                return;
            }
            if(abs( (S[last] - 'A') - (x - '0') ) % 2  ){
                cout << -1;
                return;
            }

            // 일단은 나이브하게
            rep(k, 0, 130){
                if( ('A' + ((S[last] - 'A' + k) % 26 )) != 'C') continue;
                if( ('0' + ((x - '0' + k) % 10)) != '4') continue;
                possidx[last] = k;
                v.pop_back();
                inside[v[v.size()-1]]++;
                fromside[last] = v[v.size()-1];
                break;
            }
        }
    }
    if(v.size() != 1){
        cout << -1;
        return;
    }

    rep(i, 1, N+1){
        char x = S[i];
        if('A' <= x && x <= 'Z' && inside[i] == 0) poss[possidx[i]].push_back(i);
    }

    int ans = 0, cur = 0, rest = N/2;
    while(rest){
        // cout << ans << ' ' << cur << ' ' << rest << endl;
        while(!poss[cur].empty()){
            rest--;
            ans++;
            int val = poss[cur][poss[cur].size() - 1];
            // cout << "erased " << val << endl;
            poss[cur].pop_back();
            int from = fromside[val];
            // cout << "from: " << from << endl;
            // cout << "insidefrom: " << inside[from] << endl;
            if(--inside[from] == 0){
                poss[possidx[from]].push_back(from);
                // cout << "added " << from << " to " << possidx[from] << endl;
            }
        }

        if(rest == 0) break;

        if(cur == 129) cur = 0;
        else cur++;
        ans++;
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