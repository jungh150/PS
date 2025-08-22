#include <iostream>
using namespace std;

void solve() {
    int sum = 0;
    while (true) {
        int x;
        cin >> x;
        if (x == -1) break;
        sum += x;
    }
    cout << sum << '\n';
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