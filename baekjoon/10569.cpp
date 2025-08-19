#include <iostream>
using namespace std;

void solve() {
    int v, e;
    cin >> v >> e;
    cout << 2 - v + e << '\n';
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