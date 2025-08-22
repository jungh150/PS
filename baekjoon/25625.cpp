#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int x, y;
    cin >> x >> y;
    if (x <= y) cout << y - x << '\n';
    else cout << x + y << '\n';
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