#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<bool> a(n, true);

    while (m--) {
        int x, y;
        cin >> x >> y;
        for (int i = x; i < y; i++) a[i] = false;
    }

    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (a[i]) cnt++;
    }

    cout << cnt + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}