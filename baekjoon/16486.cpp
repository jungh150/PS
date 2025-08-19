#include <iostream>
using namespace std;

void solve() {
    double d1, d2;
    cin >> d1 >> d2;
    
    cout << fixed;
    cout.precision(8);

    cout << 2 * d1 + 2 * d2 * 3.141592 << '\n';
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