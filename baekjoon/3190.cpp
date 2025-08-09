#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//          R  D  L  U
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<vector<bool>> a(n + 1, vector<bool>(n + 1, 0)); // 사과
    vector<vector<bool>> b(n + 1, vector<bool>(n + 1, 0)); // 뱀

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }

    int l;
    cin >> l;

    b[1][1] = 1;
    int curi = 1;
    int curj = 1;
    int dir = 0;
    int t = 1;
    queue<pair<int, int>> tail;
    tail.push({1, 1});

    for (int i = 0; i < l; i++) {
        int x;
        char c;
        cin >> x >> c;

        while (t <= x) {
            int nxti = curi + dx[dir];
            int nxtj = curj + dy[dir];

            if (nxti < 1 || nxti > n || nxtj < 1 || nxtj > n) { // 벽과 충돌
                cout << t << '\n';
                return 0;
            }

            tail.push({nxti, nxtj});
            if (b[nxti][nxtj]) { // 자신의 몸과 충돌
                cout << t << '\n';
                return 0;
            } else if (a[nxti][nxtj]) { // 사과가 있으면
                a[nxti][nxtj] = 0; // 사과 먹음
                b[nxti][nxtj] = 1;
            } else { // 사과가 없는 빈칸이면
                b[nxti][nxtj] = 1;
                auto [tmpi, tmpj] = tail.front();
                tail.pop();
                b[tmpi][tmpj] = 0;
            }

            curi = nxti;
            curj = nxtj;

            t++;
        }

        if (c == 'L') dir = (dir - 1 + 4) % 4; // 왼쪽으로 90도
        else if (c == 'D') dir = (dir + 1) % 4; // 오른쪽으로 90도
    }

    while(1) {
        int nxti = curi + dx[dir];
        int nxtj = curj + dy[dir];

        if (nxti < 1 || nxti > n || nxtj < 1 || nxtj > n) { // 벽과 충돌
            cout << t << '\n';
            return 0;
        }

        tail.push({nxti, nxtj});
        if (b[nxti][nxtj]) { // 자신의 몸과 충돌
            cout << t << '\n';
            return 0;
        } else if (a[nxti][nxtj]) { // 사과가 있으면
            a[nxti][nxtj] = 0; // 사과 먹음
            b[nxti][nxtj] = 1;
        } else { // 사과가 없는 빈칸이면
            b[nxti][nxtj] = 1;
            auto [tmpi, tmpj] = tail.front();
            tail.pop();
            b[tmpi][tmpj] = 0;
        }

        curi = nxti;
        curj = nxtj;

        t++;
    }
}