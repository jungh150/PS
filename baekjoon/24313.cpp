#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a1, a0, c, n0;
    cin >> a1 >> a0 >> c >> n0;

    if (a1 == c) {
        if (a0 <= n0) cout << 1 << '\n';
        else cout << 0 << '\n';
    } else if (a1 > c) {
        cout << 0 << '\n';
    } else {
        if (a0 <= n0 * (c - a1)) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}