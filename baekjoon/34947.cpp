#include <iostream>
#include <cmath>
using namespace std;

double PI = 2.0 * acos(0.0);

void solve() {
    int n, t, r, d, th, w;
    cin >> n >> t >> r >> d >> th >> w;
    
    double theta = (2 * PI * th) / 360;

    double dst1 = (2 * d + 4 * r * sin((PI - theta) / 2) + 2 * r * theta) * n;
    double dst2 = (2 * d + 4 * (r - (double) w / 100) * sin((PI - theta) / 2) + 2 * (r - (double) w / 100) * theta) * n;
    double dst3 = (2 * d + 4 * (r - (double) w / 50) * sin((PI - theta) / 2) + 2 * (r - (double) w / 50) * theta) * n;

    cout << fixed;
    cout.precision(10);

    cout << (dst1 - dst3) / t << '\n';
    cout << (dst1 - dst2) / t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}