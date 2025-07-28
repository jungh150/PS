#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];
    a[0] = 0;

    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        vector<int> b(n + 1);
        int tmpa = 0;

        // LIS
        int maxl = 1;
        b[1] = a[i];
        for (int j = i + 1; j < n + 1; j++) {
            if (a[j] > b[maxl]) {
                maxl++;
                b[maxl] = a[j];
            } else if (a[j] > a[i]) {
                int idx = lower_bound(b.begin() + 1, b.begin() + maxl + 1, a[j]) - b.begin();
                b[idx] = a[j];
            }
        }
        tmpa += maxl;

        // LDS
        maxl = 1;
        b[1] = a[i];
        for (int j = i + 1; j < n + 1; j++) {
            if (a[j] < b[maxl]) {
                maxl++;
                b[maxl] = a[j];
            } else if (a[j] < a[i]) {
                int idx = lower_bound(b.begin() + 1, b.begin() + maxl + 1, a[j], greater<>()) - b.begin();
                b[idx] = a[j];
            }
        }
        tmpa += maxl;
        
        ans = max(ans, tmpa - 1);
    }

    cout << ans << '\n';
}