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

void solve() {
    long long n;
    cin >> n;

    if (n == 0) cout << 1 << '\n';
    else cout << sq(2, n - 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}