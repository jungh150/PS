#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, curs, cnt, time;
vector<vector<int>> m;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

vector<int> targetf(int si, int sj) {
    vector<vector<int>> vst(n, vector<int>(n, -1));
    queue<pair<int, int>> q;
    vector<vector<int>> fish;

    q.emplace(si, sj);
    vst[si][sj] = 0;

    while (!q.empty()) {
        int curi = q.front().first;
        int curj = q.front().second;
        q.pop();

        if (m[curi][curj] > 0 && m[curi][curj] < curs) {
            fish.push_back({vst[curi][curj], curi, curj}); // 걸리는 시간, x 좌표, y 좌표
        }

        for (int k = 0; k < 4; k++) {
            int nxti = curi + dx[k];
            int nxtj = curj + dy[k];
            if (nxti >= 0 && nxti < n && nxtj >= 0 && nxtj < n && m[nxti][nxtj] <= curs && vst[nxti][nxtj] == -1) {
                q.emplace(nxti, nxtj);
                vst[nxti][nxtj] = vst[curi][curj] + 1;
            }
        }
    }

    if (fish.empty()) {
        return {-1, -1, -1};
    } else {
        sort(fish.begin(), fish.end());
        return fish[0];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m = vector<vector<int>>(n, vector<int>(n));
    int curi, curj;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
            if (m[i][j] == 9) {
                m[i][j] = 0;
                curi = i;
                curj = j;
            }
        }
    }

    curs = 2;
    cnt = 0;
    time = 0;

    while (1) {
        vector<int> f = targetf(curi, curj);

        if (f[0] == -1) { // 더 이상 먹을 수 있는 물고기가 없을 때
            cout << time << '\n';
            return 0;
        } else { // 먹을 수 있는 물고기가 하나라도 있을 때
            time += f[0];
            curi = f[1];
            curj = f[2];
            m[curi][curj] = 0;
            cnt++;
            if (cnt == curs) {
                curs++;
                cnt = 0;
            }
        }
    }
}