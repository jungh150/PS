#include <iostream>
#include <numeric>
using namespace std;

void solve() {
    long long x1 = 0; long long x2 = 0; long long y1 = 0; long long y2 = 0;
    for (int i = 0; i < 4; i++) {
        long long a, b;
        cin >> a >> b;
        x1 += a;
        y1 += b;
    }
    for (int i = 0; i < 4; i++) {
        long long a, b;
        cin >> a >> b;
        x2 += a;
        y2 += b;
    }
    x1 /= 2; y1 /= 2; x2 /= 2; y2 /= 2;

    long long a1 = x1 - x2;
    long long a2 = y1 - y2;
    if (a1 < 0) {
        a1 *= -1;
        a2 *= -1;
    }
    long long tmp1 = gcd(a1, a2);
    a1 /= tmp1;
    a2 /= tmp1;
    
    if (a1 == 1) cout << a2 << ' ';
    else cout << a2 << '/' << a1 << ' ';
    
    long long a3 = a1 * y1 - a2 * x1;
    a1 *= 2;
    long long tmp2 = gcd(a1, a3);
    a1 /= tmp2;
    a3 /= tmp2;

    if (a1 == 1) cout << a3 << '\n';
    else cout << a3 << '/' << a1 << '\n';
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