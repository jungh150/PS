#include <iostream>
using namespace std;

void solve() {
    int x;
    cin >> x;

    int res = 0;
    char tmp, c;
    for (int i = 0; i < x; i++) {
        cin >> tmp >> c;
        if (tmp == '!') res += tmp;
        else res += (tmp - '0');
    }
    cin >> tmp;
    if (tmp == '!') res += tmp;
    else res += (tmp - '0');

    if (res > 9) cout << "!\n";
    else cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}