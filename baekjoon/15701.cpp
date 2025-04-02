#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int sq = sqrt(n);
    int ans = 0;

    for (int i = 1; i < sq + 1; i++) {
        if (n % i == 0) {
            if (i * i == n) ans++;
            else ans += 2;
        }
    }

    cout << ans << '\n';
}