#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    while (m--) {
        int q;
        cin >> q;
        
        if (q == 1) {
            long long k;
            cin >> k;
            int idx = lower_bound(a.begin(), a.end(), k) - a.begin();
            cout << n - idx << '\n';
        } else if (q == 2) {
            long long k;
            cin >> k;
            int idx = upper_bound(a.begin(), a.end(), k) - a.begin();
            cout << n - idx << '\n';
        } else if (q == 3) {
            long long i, j;
            cin >> i >> j;
            int idx1 = lower_bound(a.begin(), a.end(), i) - a.begin();
            int idx2 = upper_bound(a.begin(), a.end(), j) - a.begin();
            cout << idx2 - idx1 << '\n';
        }
    }
}