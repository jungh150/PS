#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a % 2 == 0) cnt++;
    }

    if (cnt > n - cnt) cout << "Happy\n";
    else cout << "Sad\n";
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