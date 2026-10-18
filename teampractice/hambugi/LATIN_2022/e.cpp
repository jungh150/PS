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
        chk[a] = true; // a 먼저 채워
        // 이제 b를 채워야 함
        if (b == 0) {
            ans = 0;
        } else if (b >= 1 && !chk[b]) {
            ans = 0;
        } else if (b - 1 >= 1 && !chk[b - 1]) {
            if (b - 1 != 1 && !chk[1]) ans = 0;
            else ans = 1;
        } else if (b - 2 >= 1 && n > 2 && !chk[b - 2]) {
            if (b - 2 != 2 && !chk[2]) ans = 0;
            else ans = 2;
        } else {
            ans = b;
        }
    } else if (b != k) {
        chk[b] = true; // b 먼저 채워
        // 이제 a를 채워야 함
        if (a == 0) {
            ans = 0;
        } else if (a >= 1 && !chk[a]) {
            ans = 0;
        } else if (a - 1 >= 1 && !chk[a - 1]) {
            if (a - 1 != 1 && !chk[1]) ans = 0;
            else ans = 1;
        } else if (a - 2 >= 1 && n > 2 && !chk[a - 2]) {
            if (a - 2 != 2 && !chk[2]) ans = 0;
            else ans = 2;
        } else {
            ans = a;
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