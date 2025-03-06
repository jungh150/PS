#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long f[11];
    f[0] = 1;
    for (int i = 1; i < 11; i++) f[i] = f[i - 1] * i;

    int n, m, k;
    cin >> n >> m >> k;

    cout.precision(10);
    int ans = 0;

    for (int i = k; i <= m; i++) {
        int tmp1 = f[m] / (f[i] * f[m - i]);
        int tmp2 = f[n - m] / (f[m - i] * f[n - 2 * m + i]);
        ans += tmp1 * tmp2;
    }

    cout << (double) ans * f[m] * f[n - m] / f[n] << '\n';
}