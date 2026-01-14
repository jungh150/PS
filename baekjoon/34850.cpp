#include <iostream>
#include <vector>
using namespace std;

void solve() {
    long long x, y, p, a, b;
    cin >> x >> y >> p >> a >> b;

    long long tmp = p + b * (y - 1);
    long long ans = x * tmp - a * (x - 1) * x / 2;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}