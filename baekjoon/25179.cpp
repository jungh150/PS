#include <iostream>
using namespace std;

void solve() {
    long long n, m;
    cin >> n >> m;

    if ((n - 1) % (m + 1) != 0) cout << "Can win\n";
    else cout << "Can't win\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}