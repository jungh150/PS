#include <iostream>
using namespace std;

void solve() {
    int t;
    cin >> t;

    for (int i = 1; i < t + 1; i++) {
        cout << "Material Management " << i << '\n';
        cout << "Classification ---- End!\n";
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