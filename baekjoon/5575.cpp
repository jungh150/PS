#include <iostream>
using namespace std;

void solve() {
    int h1, m1, s1, h2, m2, s2;
    cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;
    int tmp = (h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1);

    cout << tmp / 3600 << ' ';
    tmp %= 3600;
    cout << tmp / 60 << ' ';
    tmp %= 60;
    cout << tmp << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 3;
    for (int i = 0; i < T; i++) {
        solve();
    }
}