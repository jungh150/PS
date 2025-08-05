#include <iostream>
#include <vector>
using namespace std;

long long modinv(long long x, long long n) {
    // ax = b, cx = d (a > c)
    long long a = n, b = 0;
    long long c = x % n, d = 1;
    while (c) {
        long long q = a / c;
        long long e = a- q * c, f = (b- 1LL * q * d) % n;
        a = c; b = d;
        c = e; d = f;
    }
    if (a == 1) return b < 0 ? b + n : b;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n, a;
    cin >> n >> a;

    cout << (n - a) % n << ' '; // 덧셈역
    cout << modinv(a, n) << '\n'; // 곱셈역
}