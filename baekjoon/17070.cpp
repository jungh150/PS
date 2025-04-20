#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 파이프가 놓여 있는 방향 {가로, 세로, 대각선}
int px[] = {0, -1, -1};
int py[] = {-1, 0, -1};

vector<vector<vector<int>>> d = {
    {{0, 1, 0}, {1, 1, 2}}, // 가로 상태일 때 이동할 수 있는 방법
    {{1, 0, 1}, {1, 1, 2}}, // 세로 상태일 때 이동할 수 있는 방법
    {{0, 1, 0}, {1, 0, 1}, {1, 1, 2}} // 대각선 상태일 때 이동할 수 있는 방법
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<bool>> a(n, vector<bool>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) a[i][j] = 1;
        }
    }

    queue<vector<int>> q;
    q.push({0, 1, 0});
    int ans = 0;
    
    while (!q.empty()) {
        int curi = q.front()[0];
        int curj = q.front()[1];
        int curs = q.front()[2];
        q.pop();
        if (curi == n - 1 && curj == n - 1) ans++;

        int kn = d[curs].size();
        for (int k = 0; k < kn; k++) {
            int nxti = curi + d[curs][k][0];
            int nxtj = curj + d[curs][k][1];
            int nxts = d[curs][k][2];
            if (nxti < n && nxtj < n && !a[nxti][nxtj]) {
                if ((nxts != 2) || ((!a[nxti - 1][nxtj]) && (!a[nxti][nxtj - 1]))) {
                    q.push({nxti, nxtj, nxts});
                }
            }
        }
    }

    cout << ans << '\n';
}