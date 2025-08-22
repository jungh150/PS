#include <iostream>
using namespace std;

void solve() {
    long long x, y;
    cin >> x >> y;
    if (x >= y) cout << "MMM BRAINS\n";
    else cout << "NO BRAINS\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}