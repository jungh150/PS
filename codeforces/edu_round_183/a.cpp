#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n % 3 == 0) cout << 0 << '\n';
    else if (n % 3 == 1) cout << 2 << '\n';
    else cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}