#include <iostream>
using namespace std;

void solve() {
    int s, t, d;
    cin >> s >> t >> d;
    cout << (d / (2 * s)) * t << '\n';
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