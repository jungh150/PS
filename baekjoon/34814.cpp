#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    for (int i = 0; i < m; i++) {
        int l, h;
        cin >> l >> h;

        int maxt = 0;
        for (int i = 1; i < n + 1; i++) maxt = max(maxt, a[i]);

        if (a[h] < maxt) a[l]--;
    }

    for (int i = 1; i < n + 1; i++) cout << a[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}