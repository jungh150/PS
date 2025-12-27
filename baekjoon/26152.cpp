#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<int> c;
    vector<int> sc;
    int pre = 2 * 1e9 + 1;
    for (int i = 0; i < n; i++) {
        int cur = a[i] - b[i];
        if (cur < pre) {
            c.push_back(cur);
            sc.push_back(i + 1);
            pre = cur;
        }
    }
    c.push_back(0);
    sc.push_back(n + 1);
    int sz = c.size();

    int q;
    cin >> q;

    while (q--) {
        int w;
        cin >> w;

        int l = 0;
        int r = sz;
        while (l < r) {
            int m = (l + r) / 2;
            if (c[m] >= w) l = m + 1;
            else r = m;
        }
        cout << sc[l] - 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}