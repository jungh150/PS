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
        int n, c;
        cin >> n >> c;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int curn = n;
        int ans = 0;

        for (int k = 0; k < n; k++) {
            int maxv = 0;
            int maxi = 0;

            for (int i = 0; i < curn; i++) {
                if (a[i] <= c) {
                    if (a[i] > maxv) {
                        maxv = a[i];
                        maxi = i;
                    }
                }
            }

            //for (int x: a) cout << x << ' ';
            //cout << '\n';
            //cout << a[maxi] << '\n';

            if (a[maxi] > c) ans++;
            a.erase(a.begin() + maxi);

            for (int i = 0; i < curn; i++) {
                if (a[i] <= c) a[i] *= 2;
            }

            curn--;
        }

        cout << ans << '\n';
    }
}