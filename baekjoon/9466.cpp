#include <iostream>
#include <vector>
using namespace std;

int n, v, ce;
vector<int> a;
vector<int> chk;
vector<bool> iscycle;

void dfs(int cur) {
    chk[cur] = v;
    int nxt = a[cur];
    if (chk[nxt] == -1) dfs(nxt);
    else if (chk[nxt] == chk[cur]) ce = nxt; // cycle의 기준점을 저장
    if (ce >= 0) {
        iscycle[cur] = 1;
        if (ce == cur) ce = -1; // 여기서부터는 cycle이 아니라고 표시
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