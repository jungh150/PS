#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int ans = 1;
    int n = s.size();

    if (s[0] == 'c') ans *= 26;
    else if (s[0] == 'd') ans *= 10;
    for (int i = 1; i < n; i++) {
        if (s[i] == 'c') {
            if (s[i - 1] == 'c') ans *= 25;
            else ans *= 26;
        } else {
            if (s[i - 1] == 'd') ans *= 9;
            else ans *= 10;
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