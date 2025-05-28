#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

double dx[6] = {1, 0.5, -0.5, -1, -0.5, 0.5};
double dy[6] = {0, sqrt(3)/2, sqrt(3)/2, 0, -sqrt(3)/2, -sqrt(3)/2};

int n;
set<pair<int, int>> vst;
int ans = 0;

pair<int, int> toKey(double x, double y, int scale = 100) {
    return {round(x * scale), round(y * scale)};
}

void dfs(double x, double y, int d, int cnt) {
    if (cnt > n) return;

    auto key = toKey(x, y);
    if (vst.count(key)) {
        if (cnt == n) ans++;
        return;
    }

    vst.insert(key);

    int newd1 = (d + 1) % 6;
    int newd2 = (d + 5) % 6;
    dfs(x + dx[newd1], y + dy[newd1], newd1, cnt + 1);
    dfs(x + dx[newd2], y + dy[newd2], newd2, cnt + 1);

    vst.erase(key);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    auto start = toKey(0, 0);
    vst.insert(start);
    dfs(dx[0], dy[0], 0, 0);

    cout << ans << '\n';
}