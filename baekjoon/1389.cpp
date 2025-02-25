#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);    
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int mink = (int) 10e9; // 최소 케빈 베이컨의 수
    int ans = 0; // 최소 케빈 베이컨의 수를 가진 사람의 번호

    queue<pair<int, int>> q;

    for (int s = 1; s < n + 1; s++) {
        int cnt = 0;
        vector<bool> vst(n + 1, false);
        q.emplace(s, 0);
        vst[s] = true;
        while (!q.empty()) {
            int cur = q.front().first;
            int cnttmp = q.front().second;
            q.pop();
            cnt += cnttmp;
            for (int nxt: g[cur]) {
                if (!vst[nxt]) {
                    q.emplace(nxt, cnttmp + 1);
                    vst[nxt] = true;
                }
            }
        }

        // 갱신
        if (cnt < mink) {
            mink = cnt;
            ans = s;
        }
    }

    cout << ans << '\n';
}