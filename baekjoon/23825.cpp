#include <iostream>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    cout << min(n / 2, m / 2) << '\n';
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