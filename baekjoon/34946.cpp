#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if ((a + b <= d) && (c <= d)) cout << "~.~\n";
    else if ((a + b > d) && (c > d)) cout << "T.T\n";
    else if (a + b <= d) cout << "Shuttle\n";
    else if (c <= d) cout << "Walk\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}