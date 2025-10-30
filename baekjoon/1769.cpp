#include <iostream>
using namespace std;

void solve() {
    string s;
    cin >> s;

    int cnt = 0;

    if (s.size() == 1) {
        cout << cnt << '\n';
        if (stoi(s) % 3 == 0) cout << "YES\n";
        else cout << "NO\n";
        return;
    }

    while (1) {
        int tmp = 0;
        for (char c: s) tmp += (c - '0');
        cnt++;

        if (tmp <= 9) {
            cout << cnt << '\n';
            if (tmp % 3 == 0) cout << "YES\n";
            else cout << "NO\n";
            return;
        }

        s = to_string(tmp);
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