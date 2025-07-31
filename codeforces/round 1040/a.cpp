#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == 0) ans++;
            else ans += x;
        }

        cout << ans << '\n';
    }
}