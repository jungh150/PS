#include <iostream>
using namespace std;

void solve() {
    int t, x, n;
    cin >> t >> x >> n;

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        bool psb = false;
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            if (a == x) psb = true;
        }

        if (!psb) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}