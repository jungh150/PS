#include <iostream>
#include <vector>
#include <math.h>
// #include <numbers>
using namespace std;

// double PI = 3.14159265358979323846;
double PI = 2.0 * acos(0.0);
// double PI = numbers::pi; // C++20에서 사용 가능

double ccw(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> line(n);
    for (int i = 0; i < n; i++) cin >> line[i].first >> line[i].second;

    vector<pair<int, int>> p(2);
    cin >> p[0].first >> p[0].second >> p[1].first >> p[1].second;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        double x1 = cos(2 * PI * line[i].first / 3600) * 1000;
        double y1 = sin(2 * PI * line[i].first / 3600) * 1000;
        double x2 = cos(2 * PI * line[i].second / 3600) * 1000;
        double y2 = sin(2 * PI * line[i].second / 3600) * 1000;
        double p1x = cos(2 * PI * p[0].first / 3600) * p[0].second;
        double p1y = sin(2 * PI * p[0].first / 3600) * p[0].second;
        double p2x = cos(2 * PI * p[1].first / 3600) * p[1].second;
        double p2y = sin(2 * PI * p[1].first / 3600) * p[1].second;
        if (ccw(x1, y1, x2, y2, p1x, p1y) * ccw(x1, y1, x2, y2, p2x, p2y) < 0) cnt++;
    }

    if (cnt % 2 == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}