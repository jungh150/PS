#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool vst[1000001];
int dir[] = {-1, 1, 0, 0, 0, 0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, n, m;
    cin >> a >> b >> n >> m;

    dir[2] = a;
    dir[3] = a * (-1);
    dir[4] = b;
    dir[5] = b * (-1);

    queue<pair<int, int>> q;
    q.emplace(n, 0);
    vst[n] = true;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (x == m) {
            cout << y << '\n';
            break;
        }
        for (int i = 0; i < 6; i++) {
            int nx = x + dir[i];
            if (nx >= 0 && n <= 100000 && !vst[nx]) {
                q.emplace(nx, y + 1);
                vst[nx] = true;
            }
        }
        int nx2 = x * a;
        if (nx2 >= 0 && nx2 <= 100000 && !vst[nx2]) {
            q.emplace(nx2, y + 1);
            vst[nx2] = true;
        }
        nx2 = x * b;
        if (nx2 >= 0 && nx2 <= 100000 && !vst[nx2]) {
            q.emplace(nx2, y + 1);
            vst[nx2] = true;
        }
    }
}