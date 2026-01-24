#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s1, s2;
    cin >> s1 >> s2;

    for (int i = 0; i < n; i++) {
        if (s1[i] == '?') s1[i] = '9';
    }

    if (s1.size() > s2.size()) {
        cout << s1 << '\n';
    } else if (s1.size() < s2.size()) {
        cout << -1 << '\n';
    } else {
        if (s1 >= s2) cout << s1 << '\n';
        else cout << -1 << '\n';
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