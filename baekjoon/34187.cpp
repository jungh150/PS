#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l = 0;
    int r = 2025;
    while (l < r) {
        int m = (l + r) / 2; // = x
        cout << "? " << m << endl;
        string s;
        cin >> s;
        if (s == "Cold") {
            l = m;
            r = (m + r) / 2;
        } else if (s == "Hot") {
            l = (l + m) / 2;
            r = m;
        } else if (s == "SUAPC!") {
            l = m;
            r = m;
            break;
        }
    }
    cout << "! " << l << endl;
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