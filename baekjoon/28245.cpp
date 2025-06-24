#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    while (n--) {
        long long m;
        cin >> m;
        long long mint = 9 * 1e18;
        int minx = 0;
        int miny = 0;
        for (int x = 0; x < 62; x++) {
            for (int y = x; y < 62; y++) {
                long long xpow = (long long) 1 << x;
                long long ypow = (long long) 1 << y;
                long long tmp = abs(xpow + ypow - m);
                if (tmp < mint) {
                    mint = tmp;
                    minx = x;
                    miny = y;
                }
            }
        }
        cout << minx << ' ' << miny << '\n';
    }
}