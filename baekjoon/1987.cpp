#include <iostream>
#include <vector>
using namespace std;

int r, c;
vector<string> m;
bool vst[26];
int maxc = 0;

int di[] = {1, -1, 0, 0};
int dj[] = {0, 0, 1, -1};

void dfs(int curi, int curj, int cnt) {
    if (cnt > maxc) maxc = cnt;
    for (int k = 0; k < 4; k++) {
        int nxti = curi + di[k];
        int nxtj = curj + dj[k];
        if (nxti >= 0 && nxti < r && nxtj >= 0 && nxtj < c && !vst[m[nxti][nxtj] - 'A']) {
            vst[m[nxti][nxtj] - 'A'] = true;
            dfs(nxti, nxtj, cnt + 1);
            vst[m[nxti][nxtj] - 'A'] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> r >> c;

    m = vector<string>(r);
    for (int i = 0; i < r; i++) {
        cin >> m[i];
    }

    vst[m[0][0] - 'A'] = true; 
    dfs(0, 0, 1);

    cout << maxc << '\n';
}