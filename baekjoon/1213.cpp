#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    string s;
    cin >> s;

    vector<int> a(26, 0);
    for (char c: s) {
        a[c - 'A']++;
    }

    int oddcnt = 0;
    int oddidx = -1;
    for (int i = 0; i < 26; i++) {
        if (a[i] % 2 == 1) {
            oddcnt++;
            oddidx = i;
        }
    }

    if (oddcnt >= 2) {
        cout << "I'm Sorry Hansoo\n";
        return;
    }

    string tmp = "";
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < a[i] / 2; j++) tmp += char('A' + i);
    }

    cout << tmp;
    if (oddcnt == 1) cout << char('A' + oddidx);
    reverse(tmp.begin(), tmp.end());
    cout << tmp << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}