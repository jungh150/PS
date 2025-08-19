#include <iostream>
using namespace std;

void solve() {
    int x;
    cin >> x;

    if (x % 3 == 0) cout << "S\n";
    else if (x % 3 == 1) cout << "U\n";
    else if (x % 3 == 2) cout << "O\n";
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