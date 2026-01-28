#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, m, len;
    cin >> n >> m >> len;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    a.push_back(0);
    a.push_back(len);

    sort(a.begin(), a.end());

    vector<int> b;
    for (int i = 0; i < n + 1; i++) {
        b.push_back(a[i + 1] - a[i]);
    }

    int l = 1;
    int r = len + 1;
    while (l < r) {
        int mid = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < n + 1; i++) {
            cnt += (b[i] - 1) / mid;
        }

        if (cnt <= m) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}