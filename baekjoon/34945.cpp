#include <iostream>
using namespace std;

void solve() {
    int x;
    cin >> x;

    if (2 + x >= 8) cout << "Success!";
    else cout << "Oh My God!";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}