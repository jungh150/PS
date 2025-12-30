#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    long long pre, cur;
    pre = -1e18 - 1;
    while (n--) {
        cin >> cur;
        if (cur == pre) {
            cout << 0 << '\n';
            return;
        }
        pre = cur;
    }

    cout << 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}