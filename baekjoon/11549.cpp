#include <iostream>
using namespace std;

void solve() {
    int t;
    cin >> t;
    
    int ans = 0;
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        if (x == t) ans++;
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