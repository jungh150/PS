#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> odd;
    vector<int> even;
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 == 0) {
            even.push_back(x);
            ans += x;
        } else {
            odd.push_back(x);
        }
    }

    if (odd.empty()) {
        cout << 0 << '\n';
        return;
    }

    sort(odd.begin(), odd.end(), greater<>());
    int sz = odd.size();
    int cnt = (sz - 1) / 2 + 1;
    for (int i = 0; i < cnt; i++) ans += odd[i];

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}