#include <iostream>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int a = m;
    int b = n - a;
    int c = k;
    int d = n - c;
    cout << min(a, c) + min(b, d) << '\n';
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