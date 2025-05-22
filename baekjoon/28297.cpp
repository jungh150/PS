#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

double PI = acos(-1);
vector<int> parent;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
        return true;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<tuple<double, double, double>> gear; // {x, y, r}
    for (int i = 0; i < n; i++) {
        double x, y, r;
        cin >> x >> y >> r;
        gear.push_back({x, y, r});
    }

    vector<tuple<double, int, int>> e; // {w, u, v}
    for (int i = 0; i < n; i++) {
        auto [x1, y1, r1] = gear[i];
        for (int j = i + 1; j < n; j++) {
            auto [x2, y2, r2] = gear[j];
            double a = abs(r1 - r2);
            double h = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            if (h <= r1 + r2) {
                e.push_back({0, i, j});
            } else {
                double b = sqrt(h * h - a * a);
                double alpha = asin(a / h);
                double c1, c2;
                if (r1 >= r2) {
                    c1 = r1 * (PI + 2 * alpha);
                    c2 = r2 * (PI - 2 * alpha);
                } else {
                    c1 = r2 * (PI + 2 * alpha);
                    c2 = r1 * (PI - 2 * alpha);
                }
                e.push_back({2 * b + c1 + c2, i, j});
            }
        }
    }

    int en = e.size();
    sort(e.begin(), e.end());

    parent = vector<int>(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    int cnt = 0;
    double ans = 0;
    for (auto [w, u, v]: e) {
        if (unite(u, v)) {
            cnt++;
            ans += w;
        }
        if (cnt == n - 1) break;
    }

    cout << fixed;
    cout.precision(10);
    
    cout << ans << '\n';
}