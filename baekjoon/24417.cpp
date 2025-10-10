#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int mod = 1000000007;
    
    int n;
    cin >> n;

    int f0 = 1;
    int f1 = 1;
    int f2;
    for (int i = 3; i < n + 1; i++) {
        f2 = f0 + f1;
        if (f2 >= mod) f2 -= mod;
        f0 = f1;
        f1 = f2;
    }

    cout << f1 << ' ' << max(0, n - 2) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}