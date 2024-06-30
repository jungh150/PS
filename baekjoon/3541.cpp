#include <iostream>
#include <climits>
using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int mina = INT_MAX;

    while (m--) {
        int u, d;
        cin >> u >> d;

        int gcdt = gcd(u, d);
        // lcm = u * d / gcd
        int uc = d / gcdt; // == lcm / u
        int dc = u / gcdt; // == lcm / d
        int zerosum = uc + dc;
        int newn;

        if (n % zerosum == 0) newn = zerosum;
        else newn = n % zerosum;

        int nowf = 0;
        while (newn--) {
            if (nowf - d <= 0) nowf += u;
            else nowf -= d;
        }
        
        if (nowf < mina) mina = nowf;
    }

    cout << mina << '\n';
}