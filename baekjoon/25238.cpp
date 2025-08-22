#include <iostream>
using namespace std;

void solve() {
    long long a, b;
    cin >> a >> b;
    if (a * (100 - b) >= 10000) cout << 0 << '\n';
    else cout << 1 << '\n';
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