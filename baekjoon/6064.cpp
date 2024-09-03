#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int m, n, x, y;
        cin >> m >> n >> x >> y;

        int k = 0;
        bool psb = false;
        for (int i = 0; i < 40001; i++) {
            k = m * i + x;
            if ((k - y) % n == 0) {
                psb = true;
                break;
            }
        }

        if (psb) cout << k << '\n';
        else cout << -1 << '\n';
    }
}