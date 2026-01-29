#include <iostream>
using namespace std;

void solve() {
    int n;
    long long m;
    cin >> n >> m;

    long long sumt = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        sumt += (x - 1);
    }

    if (m <= sumt) cout << "DIMI\n";
    else cout << "OUT\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}