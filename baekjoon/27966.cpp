#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    long long ans = (n - 1) + (n - 1) * (n - 2);
    cout << ans << '\n';

    for (int i = 2; i < n + 1; i++) {
        cout << 1 << ' ' << i << '\n';
    }
}