#include <iostream>
using namespace std;

void solve() {
    int x, y;
    cin >> x >> y;

    long long a = 0;
    long long tmp = 1;
    for (int i = 0; i < x; i++) {
        a += tmp;
        tmp *= 10;
    }

    long long b = 0;
    tmp = 1;
    for (int i = 0; i < y; i++) {
        b += tmp;
        tmp *= 10;
    }

    cout << a + b << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}