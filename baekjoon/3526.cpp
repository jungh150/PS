#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int MAX_VAL = 1e9;
int n, m;
vector<vector<pair<int, int>>> adj;

vector<int> bfs(int s) {
    vector<int> dst(n + 1, MAX_VAL);
    queue<int> q;
    dst[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto [nxt, color]: adj[cur]) {
            if (dst[nxt] != MAX_VAL) continue;
            dst[nxt] = dst[cur] + 1;
            q.push(nxt);
        }
    }
    return dst;
}

void solve(){
    cin >> n >> m;

    adj = vector<vector<pair<int, int>>>(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    vector<int> dst1 = bfs(1);
    vector<int> dst2 = bfs(n);
    int ans = dst1[n]; // 최단 경로의 길이

    vector<int> ansp; // 가장 이상적인 경로의 색
    vector<int> vst(n + 1, false);
    vector<int> curs;
    curs.push_back(1);
    vst[1] = true;

    for (int i = 0; i < ans; i++) {
        int minc = 1e9 + 1;
        for (int cur: curs) {
            for (auto [nxt, color]: adj[cur]) {
                if (vst[nxt]) continue;
                if (dst1[nxt] == dst1[cur] + 1 && dst1[nxt] + dst2[nxt] == ans) { // 최단 경로에 사용되는 간선만
                    if (color < minc) {
                        minc = color; // 색 중 가장 작은 수 찾기
                    }
                }
            }
        }
        vector<int> nxts;
        for (int cur: curs) {
            for (auto [nxt, color]: adj[cur]) {
                if (vst[nxt]) continue;
                if (color == minc && dst1[nxt] == dst1[cur] + 1 && dst1[nxt] + dst2[nxt] == ans) { // 그리디하게 선택
                    nxts.push_back(nxt);
                    vst[nxt] = true;
                }
            }
        }
        swap(curs, nxts);
        ansp.push_back(minc);
    }

    cout << ans << '\n';
    for (int x: ansp) cout << x << ' ';
    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}