#include <iostream>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (s[i - 1] == '2') {
            if (s[i] == '2') ans += 2;
            else ans++;
        } else if (s[i - 1] == '5') {
            if (s[i] == '5') ans += 2;
            else ans++;
        } else if (s[i - 1] == '[') {
            ans++;
        } else if (s[i - 1] == ']') {
            if (!(s[i] == '[')) ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}