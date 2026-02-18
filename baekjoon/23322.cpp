#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    cin >> a[0];

    int val = 0;
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        if (a[i] > a[0]) {
            val += (a[i] - a[0]);
            cnt++;
        }
    }

    cout << val << ' ' << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}