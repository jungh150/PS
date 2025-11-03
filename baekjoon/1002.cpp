#include <iostream>
using namespace std;

void solve() {
    int x1, y1, x2, y2, r1, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    long long dst = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    
    if (x1 == x2 && y1 == y2) {
        if (r1 == r2) cout << "-1\n";
        else cout << "0\n";
        return;
    }

    if (dst > (r1 + r2) * (r1 + r2)) cout << "0\n";
    else if (dst == (r1 + r2) * (r1 + r2)) cout << "1\n";
    else if (dst == (r2 - r1) * (r2 - r1)) cout << "1\n";
    else if (dst < (r2 - r1) * (r2 - r1)) cout << "0\n";
    else cout << "2\n";
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