#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int ans = 0;
    
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        int tmp = 0;

        if (a == b && b == c) {
            tmp = 10000 + 1000 * a;
        } else if (a == b || b == c) {
            tmp = 1000 + 100 * b;
        } else if (c == a) {
            tmp = 1000 + 100 * c;
        } else {
            int maxt = max(a, b);
            maxt = max(maxt, c);
            tmp = 100 * maxt;
        }

        ans = max(ans, tmp);
    }

    cout << ans << '\n';
}