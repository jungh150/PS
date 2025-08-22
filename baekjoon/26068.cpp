#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int ans = 0;
    while (n--) {
        char c1, c2;
        int d;
        cin >> c1 >> c2 >> d;
        if (d <= 90) ans++;
    }
    cout << ans << '\n';
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