#include <iostream>
using namespace std;

void solve() {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    if (x3 >= x2 || x4 <= x1 || y3 >= y2 || y4 <= y1) {
        cout << (x2 - x1) * (y2 - y1) << '\n';
    } else {
        cout << (x2 - x1) * (y2 - y1) - (min(x2, x4) - max(x1, x3)) * (min(y2, y4) - max(y1, y3)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}