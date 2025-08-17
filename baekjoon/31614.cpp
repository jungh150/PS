#include <iostream>
using namespace std;

void solve() {
    int h, m;
    cin >> h >> m;

    cout << h * 60 + m << '\n';
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