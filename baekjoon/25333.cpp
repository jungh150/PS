#include <iostream>
#include <vector>
using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd (y, x % y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int a, b, x;
        cin >> a >> b >> x;
        cout << x / gcd(a, b) << '\n';
    }
}