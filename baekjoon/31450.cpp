#include <iostream>
using namespace std;

void solve() {
    int m, k;
    cin >> m >> k;

    if (m % k == 0) cout << "Yes\n";
    else cout << "No\n";
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