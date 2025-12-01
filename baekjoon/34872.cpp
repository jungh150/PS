#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) cout << j + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}