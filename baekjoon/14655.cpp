#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int ans = 0;
    int n2 = 2 * n;

    for (int i = 0; i < n2; i++) {
        int x;
        cin >> x;
        if (x >= 0) ans += x;
        else ans -= x;
    }

    cout << ans << '\n';
}