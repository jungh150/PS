#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long good(long long x) {
    long long res = x;
    res -= (x / 2 + x / 3 + x / 5 + x / 7);
    res += (x / (2 * 3) + x / (2 * 5) + x / (2 * 7) + x / (3 * 5) + x / (3 * 7) + x / (5 * 7));
    res -= (x / (2 * 3 * 5) + x / (2 * 3 * 7) + x / (2 * 5 * 7) + x / (3 * 5 * 7));
    res += (x / (2 * 3 * 5 * 7));
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        long long l, r;
        cin >> l >> r;

        cout << good(r) - good(l - 1) << '\n';
    }
}