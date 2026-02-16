#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int cur = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cur += (a - b);
        cout << cur << '\n';
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