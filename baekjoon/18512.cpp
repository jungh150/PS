#include <iostream>
using namespace std;

void solve() {
    int x, y, p1, p2;
    cin >> x >> y >> p1 >> p2;

    for (int i = 0; i < 1e7; i++) {
        if (p1 < p2) {
            p1 += x;
        } else if (p1 > p2) {
            p2 += y;
        } else {
            cout << p1 << '\n';
            return;
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}