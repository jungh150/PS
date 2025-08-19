#include <iostream>
using namespace std;

void solve() {
    int x;
    cin >> x;

    if (x % 7 == 2) cout << "1\n";
    else cout << "0\n";
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