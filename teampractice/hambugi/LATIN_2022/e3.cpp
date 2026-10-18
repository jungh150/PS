#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, e;
    cin >> n >> k >> e;

    int a = e;
    int b = n - k - e;

    int ans = 0;

    if (a == b && b == k) {
        if (a == 1) ans = 2;
        else if (a == 2) ans = 3;
        else if (a == 3) ans = 3;
        else if (a == 4) ans = 2;
        else ans = 0;
    } else if (a == k) {
        if (a == 1) {
            ans = 1;
        } else if (a == 2) {
            if (b == 1) ans = 2;
            else ans = 1;
        } else if (a == 3) {
            if (b == 1) ans = 1;
            else if (b == 2) ans = 2;
            else ans = 0;
        } else if (a == 4) {
            if (b == 1) ans = 1;
            else if (b == 2) ans = 0;
            else if (b == 3) ans = 1;
            else ans = 0;
        }
    } else if (b == k) {
        if (b == 1) {
            ans = 1;
        } else if (b == 2) {
            if (a == 1) ans = 2;
            else ans = 1;
        } else if (b == 3) {
            if (a == 1) ans = 1;
            else if (a == 2) ans = 2;
            else ans = 0;
        } else if (b == 4) {
            if (a == 1) ans = 1;
            else if (a == 2) ans = 0;
            else if (a == 3) ans = 1;
            else ans = 0;
        }
    } else if (a == b) {
        if (a == 1) {
            ans = 1;
        } else if (a == 2) {
            if (k == 1) ans = 2;
            else ans = 1;
        } else if (a == 3) {
            if (k == 1) ans = 1;
            else if (k == 2) ans = 2;
            else ans = 0;
        } else if (a == 4) {
            if (k == 1) ans = 1;
            else if (k == 2) ans = 0;
            else if (k == 3) ans = 1;
            else ans = 0;
        }
    } else {
        ans = 0;
    }
    
    cout << ans << '\n';
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