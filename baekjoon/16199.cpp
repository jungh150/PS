#include <iostream>
using namespace std;

void solve() {
    int y1, m1, d1, y2, m2, d2;
    cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
    int ans3 = y2 - y1;
    if (m2 > m1 || (m2 == m1 && d2 >= d1)) cout << ans3 << '\n';
    else cout << ans3 - 1 << '\n';
    cout << ans3 + 1 << '\n';
    cout << ans3 << '\n';
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