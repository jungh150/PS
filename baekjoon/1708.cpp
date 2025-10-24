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
ll minx = 1e9;
ll miny = 1e9;
int mini = -1;

int ccw(Point &a, Point &b, Point &c) {
    ll res = (a.x * b.y + b.x * c.y + c.x * a.y) - (b.x * a.y + c.x * b.y + a.x * c.y);
    if (res > 0) return 1; // counter clock-wise
    else if (res < 0) return -1; // clock-wise
    else return 0;
}

bool compare(Point &a, Point &b) {
    int ccwv = ccw(p[0], a, b);
    if (ccwv != 0) return ccwv > 0;
    else if (a.y != b.y) return a.y < b.y;
    else return a.x < b.x;
}

void solve() {
    int n;
    cin >> n;

    p = vector<Point>(n);

    // 기준점 (최외곽 점) 찾기
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        if (p[i].y < miny || (p[i].y == miny && p[i].x < minx)) {
            minx = p[i].x;
            miny = p[i].y;
            mini = i;
        }
    }

    // p[0]과 p[mini] swap
    p[mini].x = p[0].x;
    p[mini].y = p[0].y;
    p[0].x = minx;
    p[0].y = miny;

    // 각도 정렬
    sort(p.begin() + 1, p.end(), compare);

    // 볼록 껍질 구성 (Graham Scan)
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (s.size() >= 2) {
            int idx2 = s.top();
            s.pop();
            int idx1 = s.top();
            if (ccw(p[idx1], p[idx2], p[i]) > 0) {
                s.push(idx2);
                break;
            }
        }
        s.push(i);
    }

    cout << s.size() << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}