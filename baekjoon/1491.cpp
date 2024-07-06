#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int dx[] = { 1, 0, -1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    int n, m;
    cin >> n >> m;
    vector<vector<bool>> vst(m, vector<bool>(n, false));

    int cnt = 0;
    int di = 0;
    int x = 0;
    int y = 0;
    vst[y][x] = true;
    while (true) {
        x += dx[di];
        y += dy[di];
        if (x < 0 || x >= n || y < 0 || y >= m || vst[y][x]) {
            x -= dx[di];
            y -= dy[di];
            di = (di + 1) % 4;
            cnt++;
            if (cnt > 1) {
                break;
            }
        } else {
            vst[y][x] = true;
            cnt = 0;
        }
    }

    cout << x << ' ' << y << '\n';
}