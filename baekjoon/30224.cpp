#include <iostream>
#include <string>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int n = stoi(s);

    bool flag = false;
    for (char c: s) {
        if (c == '7') {
            flag = true;
            break;
        }
    }

    if (!flag) {
        if (n % 7 != 0) cout << 0 << '\n';
        else cout << 1 << '\n';
    } else {
        if (n % 7 != 0) cout << 2 << '\n';
        else cout << 3 << '\n';
    }
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