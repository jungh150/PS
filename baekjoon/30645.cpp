#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c, n;
    cin >> r >> c >> n;

    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    sort(d.begin(), d.end());

    vector<int> maxh(c, 0);
    int idx = 0;
    int ans = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            while (idx < n && d[idx] <= maxh[j]) {
                idx++;
            }
            if (idx >= n) break;
            maxh[j] = d[idx++];
            ans++;
        }
        if (idx >= n) break;
    }

    cout << ans << '\n';
}