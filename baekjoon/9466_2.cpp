#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, v, ce;
vector<int> a;
vector<int> chk;
vector<bool> iscycle;
stack<int> path;

void dfs(int cur) {
    chk[cur] = v;
    path.push(cur); // 스택에 경로 넣어두기
    int nxt = a[cur];
    if (chk[nxt] == -1) {
        dfs(nxt);
    } else if (chk[nxt] == chk[cur]) {
        while (path.top() != nxt) { // nxt일 때까지 pop하면서 iscycle에 체크
            iscycle[path.top()] = 1;
            path.pop();
        }
        iscycle[path.top()] = 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        a.resize(n + 1);
        chk.assign(n + 1, -1);
        iscycle.assign(n + 1, 0);
        path = stack<int>();

        for (int i = 1; i < n + 1; i++) cin >> a[i];

        for (int i = 1; i < n + 1; i++) {
            if (chk[i] >= 0) continue; // 방문한 적 없으면 패스
            ce = -1;
            dfs(i);
            v++;
        }

        int ans = 0;
        for (int i = 1; i < n + 1; i++) {
            if (!iscycle[i]) ans++;
        }
        cout << ans << '\n';
    }
}