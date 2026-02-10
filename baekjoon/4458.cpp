#include <iostream>
using namespace std;

void solve() {
    string s;
    getline(cin, s);
    cout << (char) toupper(s[0]) << s.substr(1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    cin.ignore();
    for (int i = 0; i < T; i++) {
        solve();
    }
}