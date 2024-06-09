#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    long long maxn = n;
    long long cur = 1;

    while (n > cur) {
        long long rem = n % (cur * 10);
        if (rem >= 5 * cur) {
            n = n - rem + (cur * 10);
        }
        if (n > maxn) {
            maxn = n;
        }
        cur *= 10;
    }

    cout << maxn << '\n';
}