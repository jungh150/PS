#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        if (30 % (i + 1) == 0) cout << i << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}