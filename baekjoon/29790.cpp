#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, u, l;
    cin >> n >> u >> l;
    if (n >= 1000) {
        if (u >= 8000 || l >= 260) cout << "Very Good\n";
        else cout << "Good\n";
    } else {
        cout << "Bad\n";
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