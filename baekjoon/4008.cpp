#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// line 구조체
struct Line {
    ll a, b;
    double x; // 이 line이 최적으로 쓰이기 시작하는 x 경계값
    Line(ll a_, ll b_, double x_ = 0) : a(a_), b(b_), x(x_) {}
};

// 두 line의 교차점 반환
double cross(Line &f, Line &g) {
    return (double) (g.b - f.b) / (f.a - g.a);
}

void solve() {
    int n;
    cin >> n;

    ll p, q, r;
    cin >> p >> q >> r;

    vector<int> a(n + 1); // a[i] = 병사 i의 전투력
    vector<ll> ps(n + 1, 0); // ps[i] = 병사 i까지의 전투력의 누적 합
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
        ps[i] = ps[i - 1] + a[i];
    }

    vector<ll> dp(n + 1, 0); // dp[i] = 병사 i까지의 최대 전투력 합

    vector<Line> line;

    int ptr = 0;
    for (int i = 1; i < n + 1; i++) {
        ll a_ = -2 * p * ps[i - 1];
        ll b_ = p * ps[i - 1] * ps[i - 1] - q * ps[i - 1] + dp[i - 1];
        Line f(a_, b_); // 새로운 line

        while (line.size() >= 1) {
            Line g = line.back(); // 가장 최근 line
            f.x = cross(f, g);
            if (f.x < g.x) line.pop_back();
            else break;
        }

        line.push_back(f); // 새로운 line 삽입

        while (ptr + 1 < line.size() && line[ptr + 1].x <= ps[i]) ptr++;
        dp[i] = line[ptr].a * ps[i] + line[ptr].b + p * ps[i] * ps[i] + q * ps[i] + r;
    }

    cout << dp[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}