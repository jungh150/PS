#include <bits/stdc++.h>
using namespace std;

void solve() {
    auto q = [&](long long a) {
        cout << "? " << a << endl;
        long long b;
        cin >> b;
        return b;
    };

    for (int i = 0; i < 42; i++) {
        long long x = (1LL << i);
        long long res = q(x);
        if (res != x) {
            cout << "! " << x - res << endl;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}