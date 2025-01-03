#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x1, x2, a, b, c, d, e;
    cin >> x1 >> x2 >> a >> b >> c >> d >> e;

    b -= d;
    c -= e;

    int ans = a * (x2 * x2 * x2 - x1 * x1 * x1) / 3 + b * (x2 * x2 - x1 * x1) / 2 + c * (x2 - x1);
    cout << ans << '\n';
}