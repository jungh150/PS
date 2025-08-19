#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int quo = ((n - 1) * 7 + 8 - 1) / 12;
    int rem = ((n - 1) * 7 + 8 - 1) % 12 + 1;

    cout << 2024 + quo << ' ' << rem << '\n';
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