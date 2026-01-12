#include <iostream>
using namespace std;

void solve() {
    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;

    int cnt1 = 0;
    for (char c: s1) {
        if (c == 'w') cnt1++;
    }

    int cnt2 = 0;
    for (char c: s2) {
        if (c == 'w') cnt2++;
    }

    if (cnt1 > cnt2) cout << "Oryang\n";
    else if (cnt1 < cnt2) cout << "Manners maketh man\n";
    else if (s1 != s2) cout << "Its fine\n";
    else cout << "Good\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}