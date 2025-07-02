#include <iostream>
#include <vector>
using namespace std;

vector<long long> dp;

long long cnt(long long x) {
    if (x == -1 || x == 0) return 0;

    long long tmp;
    int idx = 0;

    for (int i = 0; i < 64; i++) {
        if (((long long) 1 << i) - 1 > x) {
            idx = i - 1;
            tmp = ((long long) 1 << (i - 1)) - 1;
            break;
        }
    }

    return dp[idx] + (x - tmp) + cnt(x - tmp - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long a, b;
    cin >> a >> b;

    dp = vector<long long>(64);
    dp[1] = 1;
    for (int i = 2; i < 64; i++) {
        dp[i] = 2 * dp[i - 1] + ((long long) 1 << (i - 1));
    }

    cout << cnt(b) - cnt(a - 1) << '\n';
}