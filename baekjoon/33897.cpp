#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int pre = -1;
    int cur = -1;
    int cnt = 0;
    int maxc = 0;
    int ans = 1;

    for (int i = 0; i < n; i++) {
        cin >> cur;
        if (pre > cur) {
            ans++;
            cnt = 1;
        } else {
            cnt++;
            maxc = max(maxc, cnt);
        }
        pre = cur;
    }
    
    cout << ans << ' ' << maxc << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}