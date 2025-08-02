#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        int n;
        cin >> n;
        if (n == 0) break;

        int ans = 0;
        for (int i = n; i > 0; i--) ans += i;
        cout << ans << '\n';
    }
}