#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    long long mint = 1e9 + 1;
    long long sumt = 0;

    while (n--) {
        long long x;
        cin >> x;
        mint = min(mint, x);
        sumt += x;
    }

    long long ans = sumt;
    if (-sumt > mint) ans = ans - mint - sumt;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}