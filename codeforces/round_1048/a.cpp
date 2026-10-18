#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b;
    cin >> a >> b;

    if (a == b) cout << 0 << '\n';
    else if (a < b && b % a == 0) cout << 1 << '\n';
    else if (a > b && a % b == 0) cout << 1 << '\n';
    else cout << 2 << '\n';
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