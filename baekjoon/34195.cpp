#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<bool> change(n + 1, 0);
    char c;
    cin >> c;
    char pre = c;
    for (int i = 2; i < n + 1; i++) {
        cin >> c;
        if (c != pre) change[i] = 1;
        pre = c;
    }

    int cnt = 0;
    for (int i = 2; i < n + 1; i++) {
        if (change[i - 1] && change[i]) cnt++;
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (x == 1) {
            int l, r;
            cin >> l >> r;

            if (l != 1) {
                if (change[l]) { // 1 -> 0
                    if (l - 1 >= 1 && change[l - 1]) cnt--;
                    if (l + 1 < n + 1 && change[l + 1]) cnt--;
                    change[l] = 0;
                } else { // 0 -> 1
                    if (l - 1 >= 1 && change[l - 1]) cnt++;
                    if (l + 1 < n + 1 && change[l + 1]) cnt++;
                    change[l] = 1;
                }
            }

            if (r != n) {
                r++;
                if (change[r]) { // 1 -> 0
                    if (r - 1 >= 1 && change[r - 1]) cnt--;
                    if (r + 1 < n + 1 && change[r + 1]) cnt--;
                    change[r] = 0;
                } else { // 0 -> 1
                    if (r - 1 >= 1 && change[r - 1]) cnt++;
                    if (r + 1 < n + 1 && change[r + 1]) cnt++;
                    change[r] = 1;
                }
            }
        } else if (x == 2) {
            cout << cnt << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}