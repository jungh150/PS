#include <iostream>
#include <vector>
#include <map>
using namespace std;

int mod = 1000000007;
map<long long, long long> m;

long long fib(long long n) {
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else if (n == 2) return 1;
    else {
        if (m.find(n) != m.end()) {
            return m[n];
        } else {
            if (n % 2 == 0) {
                long long tmp = (fib(n / 2) * (fib(n / 2 + 1) + fib(n / 2 - 1))) % mod;
                m[n] = tmp;
                return tmp;
            } else {
                long long tmp = (fib((n + 1) / 2) * fib((n + 1) / 2) + fib((n - 1) / 2) * fib((n - 1) / 2)) % mod;
                m[n] = tmp;
                return tmp;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;
    cout << fib(n) << '\n';
}