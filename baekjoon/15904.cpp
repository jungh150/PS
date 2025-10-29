#include <iostream>
using namespace std;

void solve() {
    string ucpc = "UCPC";
    string s;
    getline(cin, s);

    int cnt = s.size();
    int idx = 0;
    for (char c: s) {
        if (c == ucpc[idx]) idx++;
        if (idx == 4) {
            cout << "I love UCPC\n";
            return;
        }
    }

    cout << "I hate UCPC\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}