#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int l, si, sj, ei, ej;;
        cin >> l >> si >> sj >> ei >> ej;

        vector<vector<int>> vst(l, vector<int>(l, -1));
        
        queue<vector<int>> q;
        q.push({si, sj, 0});
        vst[si][sj] = 0;
        while (!q.empty()) {
            int curi = q.front()[0];
            int curj = q.front()[1];
            int cnt = q.front()[2];
            q.pop();
            for (int k = 0; k < 8; k++) {
                int nxti = curi + dx[k];
                int nxtj = curj + dy[k];
                if (nxti >= 0 && nxti < l && nxtj >= 0 && nxtj < l && vst[nxti][nxtj] == -1) {
                    q.push({nxti, nxtj, cnt + 1});
                    vst[nxti][nxtj] = cnt + 1;
                }
            }
        }

        cout << vst[ei][ej] << '\n';
    }
}