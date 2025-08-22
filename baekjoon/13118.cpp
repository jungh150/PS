#include <iostream>
using namespace std;

void solve() {
    int p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;
    int x, y, r;
    cin >> x >> y >> r;

    if (x == p1) cout << 1 << '\n';
    else if (x == p2) cout << 2 << '\n';
    else if (x == p3) cout << 3 << '\n';
    else if (x == p4) cout << 4 << '\n';
    else cout << 0 << '\n';
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