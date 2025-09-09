#include <iostream>
#include <set>
using namespace std;

void solve() {
    long long x, n;
    cin >> x >> n;

    set<long long> div;
    // n의 약수
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            div.insert(i);
            div.insert(n / i);
        }
    }
    // n + 1의 약수
    for (long long i = 1; i * i <= n + 1; i++) {
        if ((n + 1) % i == 0) {
            div.insert(i);
            div.insert((n + 1) / i);
        }
    }

    long long ans = 0;
    for (long long d: div) {
        if (d < x) continue;
        if (((x + 2 * n) / d - (x - 1) / d) % 2 == 1) ans++;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}