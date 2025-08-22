#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    int n4 = 0;
    int n5 = 0;
    string s;
    cin >> s;
    for (char c: s) {
        if (c == 'M') n1++;
        else if (c == 'O') n2++;
        else if (c == 'B') n3++;
        else if (c == 'I') n4++;
        else if (c == 'S') n5++;
    }
    if (n1 > 0 && n2 > 0 && n3 > 0 && n4 > 0 && n5 > 0) cout << "YES\n";
    else cout << "NO\n";
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