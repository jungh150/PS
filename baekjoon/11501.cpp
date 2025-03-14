#include <iostream>
#include <vector>
#include <algorithm>
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

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<int> b(n);
        for (int i = 0; i < n; i++) b[i] = a[i];

        int idx = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] >= a[idx]) idx = i;
            b[i] = a[idx];
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (b[i] - a[i]);
        }

        cout << ans << '\n';
    }
}