#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ans += a;
    }

    if (ans > 0) cout << "Right\n";
    else if (ans == 0) cout << "Stay\n";
    else cout << "Left\n";
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