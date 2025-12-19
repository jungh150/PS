#include <iostream>
using namespace std;

void solve() {
    int r, c;
    cin >> r >> c;

    if (r == 1) {
        if (c == 1) {
            cout << "dohoon\n";
        } else {
            cout << "jinseo\n";
            cout << "1 1\n";
        }
    } else if (c == 1) {
        if (r == 1) {
            cout << "dohoon\n";
        } else {
            cout << "jinseo\n";
            cout << "1 1\n";
        }
    } else {
        if (r == c) {
            cout << "dohoon\n";
        } else {
            cout << "jinseo\n";
            cout << min(r, c) << " " << min(r, c) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}