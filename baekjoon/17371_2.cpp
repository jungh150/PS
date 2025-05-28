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

    int mind = 1e9;
    int minp = 0;
    for (int i = 0; i < n; i++) {
        int maxd = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            auto [x1, y1] = p[i];
            auto [x2, y2] = p[j];
            int dst = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
            maxd = max(maxd, dst);
        }
        if (maxd < mind) {
            mind = maxd;
            minp = i;
        }
    }

    cout << p[minp].first << ' ' << p[minp].second << '\n';
}