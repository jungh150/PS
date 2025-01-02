#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        long long n, a, b;
        cin >> n >> a >> b;

        long long sml = min(a, b);
        long long tmp = pow(2, n);
        int ans = 0;
        while (sml % tmp != 0) {
            ans++;
            tmp /= 2;
        }

        cout << ans << '\n';
    }
}