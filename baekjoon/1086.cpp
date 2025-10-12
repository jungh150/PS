#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int n, k, totlen;
vector<string> a;
vector<int> remt;
vector<int> rema;
vector<vector<long long>> dp;

long long td(int cur, int mod) {
    if (dp[cur][mod] != -1) return dp[cur][mod];

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cur & (1 << i)) cnt += a[i].size();
    }

    if (cnt == totlen && mod == 0) return dp[cur][mod] = 1;

    long long res = 0;
    for (int i = 0; i < n; i++) {
        if (!(cur & (1 << i))) {
            int newmod = (mod + rema[i] * remt[cnt]) % k;
            res += td(cur | (1 << i), newmod);
        }
    }

    return dp[cur][mod] = res;
}

void solve() {
    cin >> n;

    a = vector<string>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cin >> k;

    remt = vector<int>(1000);
    int tmp = 1;
    for (int i = 0; i < 1000; i++) {
        tmp %= k;
        remt[i] = tmp;
        tmp *= 10;
    }

    rema = vector<int>(n);
    for (int i = 0; i < n; i++) {        
        int sz = a[i].size();
        totlen += sz;
        tmp = 0;
        for (int j = 0; j < sz; j++) {
            tmp += (((a[i][sz - j - 1] - '0') % k) * remt[j]);
            tmp %= k;
        }
        rema[i] = tmp;
    }

    long long fr2 = 1;
    for (int i = 1; i <= n; i++) fr2 *= i;

    // dp[i][j]: 지금까지 사용한 원소의 비트마스킹 값이 i이고 그 때까지의 합의 나머지가 j인 경우의 수
    dp = vector<vector<long long>>((1 << n), vector<long long>(k, -1));
    long long fr1 = td(0, 0);

    if (fr1 == 0) {
        fr2 = 1;
    } else {
        long long tmp = gcd(fr1, fr2);
        fr1 /= tmp;
        fr2 /= tmp;
    }
    
    cout << fr1 << '/' << fr2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}