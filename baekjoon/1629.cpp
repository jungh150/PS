#include <iostream>
using namespace std;

long long divpow(long long a, long long b, long long c) {
    if (b == 1) return a % c;
    long long tmp = divpow(a, b / 2, c) % c;
    if (b % 2 == 0) return (tmp * tmp) % c;
    else return (((tmp * tmp) % c) * (a % c)) % c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long a, b, c;
    cin >> a >> b >> c;

    cout << divpow(a, b, c) << '\n';
}