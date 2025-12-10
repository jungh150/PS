#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int cnt = 1;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) cnt++;
        else break;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}