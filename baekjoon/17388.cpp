#include <iostream>
using namespace std;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    if (a + b + c >= 100) {
        cout << "OK\n";
    } else {
        if (a < b && a < c) {
            cout << "Soongsil\n";
        } else {
            if (b < c) cout << "Korea\n";
            else cout << "Hanyang\n";
        }
    }
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