#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    while (n--) {
        string s;
        int x;
        cin >> s >> x;
        if (x == 2026) cout << s << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}