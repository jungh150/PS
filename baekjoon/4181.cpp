#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

vector<Point> p;
ll minx = 1e10;
ll miny = 1e10;
int mini = -1;

int ccw(Point &a, Point &b, Point &c) {
    ll res = (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
    if (res > 0) return 1; // counter clock-wise
    else if (res < 0) return -1; // clock-wise
    else return 0;
}

ll dist(Point &a, Point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool compare(Point &a, Point &b) {
    int ccwv = ccw(p[0], a, b);
    if (ccwv != 0) return ccwv > 0;
    return dist(p[0], a) < dist(p[0], b); // 거리가 가까운 순서대로
}

void solve() {
    int n;
    cin >> n;

    // 기준점 (최외곽 점) 찾기
    int idx = 0;
    for (int i = 0; i < n; i++) {
        ll tmpx, tmpy;
        char c;
        cin >> tmpx >> tmpy >> c;
        if (c == 'Y') {
            p.push_back({x: tmpx, y: tmpy});
            if (p[idx].x < minx || (p[idx].x == minx && p[idx].y < miny)) {
                minx = p[idx].x;
                miny = p[idx].y;
                mini = idx;
            }
            idx++;
        }
    }

    // p[0]과 p[mini] swap
    p[mini].x = p[0].x;
    p[mini].y = p[0].y;
    p[0].x = minx;
    p[0].y = miny;

    // 각도 정렬
    sort(p.begin() + 1, p.end(), compare);
    int m = idx - 1;
    while (m > 1 && ccw(p[0], p[m], p[m - 1]) == 0) m--;
    reverse(p.begin() + m, p.end());

    cout << idx << '\n';
    for (auto tmpp: p) cout << tmpp.x << ' ' << tmpp.y << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}