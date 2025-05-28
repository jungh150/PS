#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
using namespace std;

pair<int, int> firstLogic(const vector<pair<int, int>>& p) {
    int n = p.size();
    int maxd = 0;
    int maxp1 = 0, maxp2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = p[i].first - p[j].first;
            int dy = p[i].second - p[j].second;
            int dst = dx * dx + dy * dy;
            if (dst > maxd) {
                maxd = dst;
                maxp1 = i;
                maxp2 = j;
            }
        }
    }

    int mind = 1e9;
    int minp = 0;
    for (int i = 0; i < n; i++) {
        int dx1 = p[i].first - p[maxp1].first;
        int dy1 = p[i].second - p[maxp1].second;
        int dst1 = dx1 * dx1 + dy1 * dy1;

        int dx2 = p[i].first - p[maxp2].first;
        int dy2 = p[i].second - p[maxp2].second;
        int dst2 = dx2 * dx2 + dy2 * dy2;

        int tmp = max(dst1, dst2);
        if (tmp < mind) {
            mind = tmp;
            minp = i;
        }
    }

    return p[minp];
}

pair<int, int> secondLogic(const vector<pair<int, int>>& p) {
    int n = p.size();
    int mind = 1e9;
    int minp = 0;

    for (int i = 0; i < n; i++) {
        int maxd = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            int dx = p[i].first - p[j].first;
            int dy = p[i].second - p[j].second;
            int dst = dx * dx + dy * dy;
            maxd = max(maxd, dst);
        }
        if (maxd < mind) {
            mind = maxd;
            minp = i;
        }
    }

    return p[minp];
}

int main() {
    srand(time(0));
    const int n = 4;
    for (int t = 0; t < 1000000; t++) {
        vector<pair<int, int>> points;
        while (points.size() < n) {
            int x = rand() % 11 - 5; // [-5, 5]
            int y = rand() % 11 - 5;
            pair<int, int> pt = {x, y};
            bool dup = false;
            for (auto& p : points) {
                if (p == pt) {
                    dup = true;
                    break;
                }
            }
            if (!dup) points.push_back(pt);
        }

        auto a = firstLogic(points);
        auto b = secondLogic(points);

        if (a != b) {
            cout << "반례 발견!\n";
            cout << n << '\n';
            for (auto [x, y] : points) cout << x << ' ' << y << '\n';
            cout << "First: " << a.first << ' ' << a.second << '\n';
            cout << "Second: " << b.first << ' ' << b.second << '\n';
            return 0;
        }
    }

    cout << "모든 테스트에서 동일한 결과를 냄\n";
    return 0;
}
