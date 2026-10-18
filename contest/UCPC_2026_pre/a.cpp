#include <bits/stdc++.h>
using namespace std;

void solve() {
    int d, m, v;
    cin >> d >> m >> v;

    if ((60 - m) * v > d) cout << "run\n";
    else cout << "late\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}