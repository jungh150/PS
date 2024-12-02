#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int t, r;
        cin >> t >> r;
        k -= r;
        
        if (k < 0) {
            cout << i + 1 << ' ' << 1 << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
}