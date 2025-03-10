#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        int n;
        cin >> n;

        if (n == 0) break;

        int zeron = 0;
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == 0) zeron++;
            else a.push_back(x);
        }

        sort(a.begin(), a.end());

        int idx = n - zeron - 1;
        int curn = 1;
        int ans = 0;
        bool done = true;

        while (idx >= 2) {
            if (idx == 2) {
                ans += curn * a[idx];
                idx--;
                done = false;
            } else {
                ans += curn * (a[idx] + a[idx - 1]);
                curn *= 10;
                idx -= 2;
                done = true;
            }
        }

        if (zeron == 0) {
            if (done) ans += curn * (a[idx] + a[idx - 1]);
            else ans += curn * a[idx] + curn * 10 * a[idx - 1];
        } else if (zeron == 1) {
            if (done) ans += curn * a[idx] + curn * 10 * a[idx - 1];
            else ans += curn * 10 * (a[idx] + a[idx - 1]);
        } else {
            if (zeron % 2 == 0) {
                int tmp = zeron / 2;
                while (tmp--) curn *= 10;
                if (done) ans += curn * (a[idx] + a[idx - 1]);
                else ans += curn * a[idx] + curn * 10 * a[idx - 1];
            } else {
                int tmp = zeron / 2;
                while (tmp--) curn *= 10;
                if (done) ans += curn * (a[idx] + 10 * a[idx - 1]);
                else ans += curn * 10 * (a[idx] + a[idx - 1]);
            }
        }
        
        cout << ans << '\n';
    }
}