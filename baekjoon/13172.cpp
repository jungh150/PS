#include <iostream>
#include <vector>
using namespace std;

int MOD = 1000000007;

long long sq(long long x, long long n) {
    if (n == 0) return 1;
    long long tmp = sq(x , n / 2) % MOD;
    if (n % 2 == 0) return (tmp * tmp) % MOD;
    else return (((tmp * tmp) % MOD) * x) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> m;

    int ans = 0;

    for (int i = 0; i < m; i++) {
        long long a, b;
        cin >> b >> a;

        int tmp = (a * sq(b, MOD - 2)) % MOD;
        ans = (ans + tmp) % MOD;
    }

    cout << ans << '\n';
}