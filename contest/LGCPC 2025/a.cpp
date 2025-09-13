#include <bits/stdc++.h>
using namespace std;

int mod = 998244353;
int p, n, m;
vector<int> s;
vector<vector<int>> adj;

int bfs(int cur) {
    int vst = 0;
    queue<int> q;
    q.push(cur);
    vst |= (1 << cur);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        for (int nxt: adj[cur]) {
            if (!(vst & (1 << nxt))) {
                q.push(nxt);
                vst |= (1 << nxt);
            }
        }
    }
    return vst;
}

void solve() {
    cin >> p;

    vector<int> nump(p, 0); // 조합 점수 개수
    vector<long long> sump(p, 0); // 조합 점수 합

    for (int k = 0; k < p; k++) {
        cin >> n >> m;

        s = vector<int>(n + 1);
        for (int i = 1; i < n + 1; i++) cin >> s[i];

        adj = vector<vector<int>>(n + 1);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[b].push_back(a);
        }

        vector<int> bm(n + 1); // 각 섭태에 대한 비트마스킹
        for (int i = 1; i < n + 1; i++) { // 모든 섭태에 대해서
            bm[i] = bfs(i);
        }

        // cout << "bm\n";
        // for (int x: bm) cout << x << ' ';
        // cout << '\n';

        set<int> comb; // 가능한 섭태 조합
        for (int i = 0; i <= (1 << 11); i++) {
            int b = 0;
            for (int j = 1; j < n + 1; j++) {
                if (i & (1 << j)) b |= bm[j];
            }
            comb.insert(b);
        }

        // cout << "comb\n";
        // for (int x: comb) cout << x << ' ';
        // cout << '\n';

        nump[k] = comb.size();
        for (int b: comb) {
            long long tmp = 0;
            for (int i = 1; i < n + 1; i++) {
                if (b & (1 << i)) tmp += s[i];
            }
            sump[k] += tmp;
        }
    }

    long long ans = 0;

    for (int i = 0; i < p; i++) {
        long long tmp = 1; // 나머지 numt의 곱
        for (int j = 0; j < p; j++) {
            if (i != j) {
                tmp *= nump[j];
                tmp = tmp % mod;
            }
        }
        
        tmp *= sump[i];
        tmp = tmp % mod;

        ans += tmp;
        ans = ans % mod;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}