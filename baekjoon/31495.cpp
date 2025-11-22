#include <iostream>
using namespace std;

void solve() {
    string s;
    getline(cin, s);

    int n = s.size();

    if (s[0] != '"' || s[n - 1] != '"') {
        cout << "CE\n";
        return;
    }

    string ans = "";
    for (int i = 1; i < n - 1; i++) ans += s[i];

    if (ans.size() == 0) {
        cout << "CE\n";
        return;
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