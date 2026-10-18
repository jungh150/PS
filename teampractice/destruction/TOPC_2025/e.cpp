#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i < k + 1; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = i;
    }

    int u1, v1, u2, v2;
    cin >> u1 >> v1 >> u2 >> v2;

    int cntrec = (u2 - u1 + 1) * (v2 - v1 + 1);

    int l = 0;
    int r = k + 1;
    while (l < r) {
        int mid = (l + r) / 2;

        bool psb = 1;

        vector<vector<bool>> vst(n + 1, vector<bool>(m + 1, 0));
        for (int si = u1; si <= u2; si++) {
            for (int sj = v1; sj <= v2; sj++) {
                if (a[si][sj] > mid) {
                    psb = 0;
                    break;
                }
                if (vst[si][sj]) continue;

                queue<pair<int, int>> q;
                int cntall = 1;
                int cntst = 0;
                if (a[si][sj] > 0) cntst++;

                q.emplace(si, sj);
                vst[si][sj] = 1;

                while (!q.empty()) {
                    auto [curi, curj] = q.front();
                    q.pop();
                    for (int i = 0; i < 4; i++) {
                        int nxti = curi + dx[i];
                        int nxtj = curj + dy[i];
                        if (nxti <= 0 || nxti > n || nxtj <= 0 || nxtj > m || a[nxti][nxtj] > mid || vst[nxti][nxtj]) continue;
                        q.emplace(nxti, nxtj);
                        vst[nxti][nxtj] = 1;
                        cntall++;
                        if (a[nxti][nxtj] > 0) cntst++;
                    }
                }

                // cout << "l = " << l << ", r = " << r << '\n';
                // cout << "mid = " << mid << '\n';
                // cout << cntall << ' ' << cntst << '\n';

                if (cntall - cntrec < cntst) {
                    psb = 0;
                    break;
                }
            }
            if (!psb) break;
        }

        if (psb) r = mid;
        else l = mid + 1;
    }

    if (l >= k + 1) cout << -1 << '\n';
    else cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}