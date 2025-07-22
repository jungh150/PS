#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long gcd(long long x, long long y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        long long a, b, k;
        cin >> a >> b >> k;

        long long tmp = gcd(a, b);
        
        if ((a / tmp <= k) && (b / tmp <= k)) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
}