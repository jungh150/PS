#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n > 4500) cout << "Round 1\n";
    else if (n > 1000) cout << "Round 2\n";
    else if (n > 25) cout << "Round 3\n";
    else cout << "World Finals\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": ";
        solve();
    }
}