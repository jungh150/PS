#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct Line {
    ll a, b;
    double x;
    Line(ll a_, ll b_, double x_ = 0) : a(a_), b(b_), x(x_) {}
};

int n;
vector<int> a, b;
vector<ll> dp;
vector<Line> line;

double cross(Line &f, Line &g) {
    return (double) (g.b - f.b) / (f.a - g.a);
}

void solve() {
    int n;
    cin >> n;

    // a[i] = 나무의 높이
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // b[i] = 나무에 대한 충전 비용
    b = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    // dp[i] = i번째 나무의 높이를 1로 만들기 위한 최소 비용
    dp = vector<ll>(n, 0);

    int ptr = 0;
    for (int i = 1; i < n; i++) {
        Line f(b[i - 1], dp[i - 1]); // 새로운 line

        while (line.size() >= 1) {
            Line g = line.back(); // 가장 최근 line
            f.x = cross(f, g);
            if (f.x < g.x) line.pop_back();
            else break;
        }

        line.push_back(f); // 새로운 line 삽입

        while (ptr + 1 < line.size() && line[ptr + 1].x <= a[i]) ptr++;
        dp[i] = line[ptr].a * a[i] + line[ptr].b;
    }

    cout << dp[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}