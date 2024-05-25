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

    vector<pair<int, int>> itv (n);
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        itv[i].first = l;
        itv[i].second = r;
    }

    sort(itv.begin(), itv.end());

    for (int i = 0; i < n - 1; i++) {
        int l = i;
        int r = n;
        int m;
        while (l < r) {
            m = (l + r) / 2;
            if (itv[m].first <= itv[i].second) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        ans += (l - 1 - i);
    }

    cout << ans << '\n';
}