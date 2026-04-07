#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << "NO\n";
        return;
    }

    vector<int> pow(20);
    int tmp = 1;
    for (int i = 0; i < 20; i++) {
        pow[i] = tmp;
        tmp *= 3;
    }

    for (int i = 19; i >= 0; i--) {
        if (n >= pow[i]) n -= pow[i];
    }

    if (n == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}