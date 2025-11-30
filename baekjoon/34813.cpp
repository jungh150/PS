#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;

    if (s[0] == 'F') cout << "Foundation\n";
    else if (s[0] == 'C') cout << "Claves\n";
    else if (s[0] == 'V') cout << "Veritas\n";
    else if (s[0] == 'E') cout << "Exploration\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}