#include <iostream>
#include <vector>
using namespace std;

int k, v, e;
vector<vector<int>> g;
vector<int> color; // 방문 여부 배열 + 색 기록 배열
bool isBipartite;

void dfs(int cur, int prec) {
    // curc: 현재 색 (이전 색과 다른 색으로 선택)
    int curc;
    if (prec == 0) curc = 1;
    else curc = 0;
    // color 배열에 방금 구한 현재 색 (curc) 기록
    color[cur] = curc;
    // cur과 인접한 정점 nxt들에 대해
    for (int nxt: g[cur]) {
        // nxt가 방문한 적 없는 정점이라면, dfs 호출
        if (color[nxt] == -1) dfs(nxt, curc);
        // nxt가 방문한 적 있는 정점이라면, 현재 색과 같은 색인지 체크
        else if (color[nxt] == curc) isBipartite = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> k;
    while (k--) {
        cin >> v >> e;
        g = vector<vector<int>>(v + 1);
        color = vector<int>(v + 1, -1); // 방문하지 않았다는 의미로 -1으로 초기화

        for (int i = 0; i < e; i++) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        isBipartite = true; // true로 초기화
        for (int i = 1; i < v + 1; i++) {
            if (color[i] == -1) { // 아직 방문하지 않았다면
                dfs(i, 0);
            }
        }

        if (isBipartite) cout << "YES\n";
        else cout << "NO\n";
    }
}