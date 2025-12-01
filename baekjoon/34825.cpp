#include <iostream>
using namespace std;

void solve() {
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    long long xdif = 0;
    long long ydif = 0;

    if (min(x1, x2) < 0) xdif = -min(x1, x2);
    if (min(y1, y2) < 0) ydif = -min(y1, y2);

    x1 += xdif;
    x2 += xdif;
    y1 += ydif;
    y2 += ydif;
    
    long long dst = abs(x1 - x2) + abs(y1 - y2);

    if (dst % 2 == 1) {
        cout << -1 << '\n';
        return;
    }

    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    if (y1 <= y2) cout << (x1 + x2) / 2 - xdif << ' ' << (y1 + y2 + 1) / 2 - ydif << '\n';
    else cout << (x1 + x2) / 2 - xdif << ' ' << (y1 + y2) / 2 - ydif << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}