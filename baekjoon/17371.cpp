#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;

    int maxd = 0;
    int maxp1 = 0;
    int maxp2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [x1, y1] = p[i];
            auto [x2, y2] = p[j];
            int dst = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
            if (dst > maxd) {
                maxd = dst;
                maxp1 = i;
                maxp2 = j;
            }
        }
    }

    auto [mx1, my1] = p[maxp1];
    auto [mx2, my2] = p[maxp2];
    int mind = 1e9;
    int minp = 0;
    for (int i = 0; i < n; i++) {
        auto [x, y] = p[i];
        int dst1 = (x - mx1) * (x - mx1) + (y - my1) * (y - my1);
        int dst2 = (x - mx2) * (x - mx2) + (y - my2) * (y - my2);
        int tmp = max(dst1, dst2);
        if (tmp < mind) {
            mind = tmp;
            minp = i;
        }
    }

    cout << p[minp].first << ' ' << p[minp].second << '\n';
}