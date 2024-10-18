#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, r;
    cin >> n >> r;

    int minx = 100, maxx = -100;
    int miny = 100, maxy = -100;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x < minx) minx = x;
        if (x > maxx) maxx = x;
        if (y < miny) miny = y;
        if (y > maxy) maxy = y;
        a.emplace_back(x, y);
    }

    int maxc = 0;
    int ansx, ansy;
    for (int i = minx; i <= maxx; i++) {
        for (int j = miny; j <= maxy; j++) {
            int cnt = 0;
            for (int k = 0; k < n; k++) {
                if (sqrt((a[k].first - i) * (a[k].first - i) + (a[k].second - j) * (a[k].second - j)) <= r) {
                    cnt++;
                }
            }
            if (cnt > maxc) {
                ansx = i;
                ansy = j;
                maxc = cnt;
            }
        }
    }

    cout << ansx << ' ' << ansy << '\n';
}