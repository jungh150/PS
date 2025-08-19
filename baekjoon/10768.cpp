#include <iostream>
using namespace std;

void solve() {
    int m, d;
    cin >> m >> d;
    if (m <= 1 || (m == 2 && d < 18)) cout << "Before\n";
    else if (m == 2 && d == 18) cout << "Special\n";
    else cout << "After\n";
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