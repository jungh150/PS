#include <iostream>
using namespace std;

void solve() {
    string s1;
    cin >> s1;
    int n;
    cin >> n;

    int ans = 0;
    while (n--) {
        string s2;
        cin >> s2;
        if (s1 == s2) ans++;
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