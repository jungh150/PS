#include <bits/stdc++.h>
using namespace std;

void solve() {
    int x, y, r;
    cin >> x >> y >> r;

    for (int i = -50; i < 50; i++) {
        for (int j = -50; j < 50; j++) {
            if ((x - i) * (x - i) + (y - j) * (y - j) == r * r) {
                cout << i << ' ' << j << '\n';
                return;
            }
        }
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