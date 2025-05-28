#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int dx[6] = {1, 1, -1, -1, -1, 1};
int dy[6] = {0, 1, 1, 0, -1, -1};

int n;
set<pair<int, int>> vst;
int ans = 0;

void dfs(double x, double y, int d, int cnt) {
    if (cnt > n) return;

    if (vst.count({x, y})) {
        if (cnt == n) ans++;
        return;
    }

    vst.insert({x, y});

    int newd1 = (d + 1) % 6;
    int newd2 = (d + 5) % 6;
    dfs(x + dx[newd1], y + dy[newd1], newd1, cnt + 1);
    dfs(x + dx[newd2], y + dy[newd2], newd2, cnt + 1);

    vst.erase({x, y});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    vst.insert({0, 0});
    dfs(dx[0], dy[0], 0, 0);

    cout << ans << '\n';
}