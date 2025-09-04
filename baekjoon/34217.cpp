#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a + c == b + d) cout << "Either\n";
    else if (a + c < b + d) cout << "Hanyang Univ.\n";
    else cout << "Yongdap\n";
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