#include <iostream>
using namespace std;

void solve() {
    int a, p, c;
    cin >> a >> p >> c;
    cout << max(a + c, p) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}