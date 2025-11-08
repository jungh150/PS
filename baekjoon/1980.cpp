#include <iostream>
using namespace std;

void solve() {
    int n, m, t;
    cin >> n >> m >> t;

    int maxc = 10000;
    int maxh = 0;
    for (int i = 0; n * i <= t; i++) {
        int tmp = t - n * i;
        int cola = tmp % m;
        int ham = i + tmp / m;
        if (cola < maxc) {
            maxc = cola;
            maxh = ham;
        } else if (cola == maxc) {
            maxh = max(maxh, ham);
        }
    }

    cout << maxh << ' ' << maxc << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}