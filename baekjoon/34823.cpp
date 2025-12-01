#include <iostream>
using namespace std;

void solve() {
    int y, c, p;
    cin >> y >> c >> p;

    cout << min(min(y, p), c / 2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}