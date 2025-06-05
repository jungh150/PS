#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, s, e;
    cin >> n >> s >> e;

    double ans = 0;

    while (n--) {
        int r, a, d;
        cin >> r >> a >> d;

        ans += (double) (e / (r + a)) * d;
        ans -= (double) (s / (r + a)) * d;
        ans += (double) max(0, (e % (r + a) - r)) * d / a;
        ans -= (double) max(0, (s % (r + a) - r)) * d / a;
    }

    cout << fixed;
    cout.precision(10);
    
    cout << ans / (e - s) << '\n';
}