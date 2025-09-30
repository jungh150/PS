#include <iostream>
#include <vector>
using namespace std;

void solve() {
    long long x, m;
    cin >> x >> m;

    cout << x * (m + 1) << '\n';
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