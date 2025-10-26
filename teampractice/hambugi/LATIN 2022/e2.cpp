#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k, e;
    cin >> n >> k >> e;

    vector<bool> chk(1001, false);
    chk[k] = true;

    int a = e;
    int b = n - k - e;

    int ans = 0;
    
    if (a != k && b != k && a != b) {
        ans = 0;
    } else if (a != k) {
        if (a == b && a == 1) { // 공통이 a
            ans = 1;
        } else if (a == b && a == 2) {
            if (b == 1) ans = 2;
            else ans = 1;
        } else if (a == b && a == 3) {
            if (b == 1) ans = 1;
            else if (b == 2) ans = 2;
            else ans - 0;
        } else if (a == b && a == 4) {
            if (b == 1) ans = 1;
            else if (b == 3) ans = 1;
            else ans = 0;
        } else if (b == k && b == 1) {
            ans = 1;
        } else if (b == k && b == 2) {
            if (a == 1) ans = 2;
            else ans = 1;
        } else if (b == k && b == 3) {
            if (a == 1) ans = 1;
            else if (a == 2) ans = 2;
            else ans - 0;
        } else if (b == k && b == 4) {
            if (a == 1) ans = 1;
            else if (a == 3) ans = 1;
            else ans = 0;
        } else {
            ans = b;
            chk[a] = true; // a 먼저 채워
            // 이제 b를 채워야 함
            if (b == 0) {
                ans = min(ans, 0);
            }
            if (b >= 1 && !chk[b]) {
                ans = min(ans, 0);
            }
            if (b - 1 >= 1 && !chk[b - 1]) {
                if (b - 1 != 1 && !chk[1]) ans = min(ans, 0);
                else ans = min(ans, 1);
            }
            if (b - 2 >= 1 && n > 2 && !chk[b - 2]) {
                if (b - 2 != 2 && !chk[2]) ans = min(ans, 0);
                else ans = min(ans, 2);
            }
        }
    } else if (b != k) {
        // 공통이 a
        if (a == 1) {
            ans = 1;
        } else if (a == 2) {
            if (b == 1) ans = 2;
            else ans = 1;
        } else if (a == 3) {
            if (b == 1) ans = 1;
            else if (b == 2) ans = 2;
            else ans - 0;
        } else if (a == 4) {
            if (b == 1) ans = 1;
            else if (b == 3) ans = 1;
            else ans = 0;
        } else {
            ans = a;
            chk[b] = true; // b 먼저 채워
            // 이제 a를 채워야 함
            if (a == 0) {
                ans = min(ans, 0);
            }
            if (a >= 1 && !chk[a]) {
                ans = min(ans, 0);
            }
            if (a - 1 >= 1 && !chk[a - 1]) {
                if (a - 1 != 1 && !chk[1]) ans = min(ans, 0);
                else ans = min(ans, 1);
            }
            if (a - 2 >= 1 && n > 2 && !chk[a - 2]) {
                if (a - 2 != 2 && !chk[2]) ans = min(ans, 0);
                else ans = min(ans, 2);
            }
        }
    } else {
        if (a == 1) ans = 2;
        else if (a == 2) ans = 3;
        else if (a == 3) ans = 3;
        else if (a == 4) ans = 2;
        else ans = 0;
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