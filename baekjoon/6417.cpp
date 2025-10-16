#include <iostream>
#include <cmath>
using namespace std;

int n;

void solve() {
    for (int k = sqrt(n) + 1; k > 1; k--) {
        bool psb = true;
        int cur = n;
        for (int i = 0; i < k; i++) {
            if (cur - 1 < 0 || (cur - 1) % k != 0) {
                psb = false;
                break;
            }
            cur = ((cur - 1) / k) * (k - 1);
            if (cur < 0) {
                psb = false;
                break;
            }
        }
        if (psb) {
            cout << n << " coconuts, " << k << " people and 1 monkey\n";
            return;
        }
    }
    cout << n << " coconuts, no solution\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> n;
        if (n == -1) return 0;
        solve();
    }
}