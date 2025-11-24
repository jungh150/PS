#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> cnt(5, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int ans = 0;

    ans += cnt[4];

    ans += min(cnt[1], cnt[3]);
    int cnt1 = cnt[1] - min(cnt[1], cnt[3]);
    int cnt3 = cnt[3] - min(cnt[1], cnt[3]);

    ans += (cnt[2] / 2);
    int cnt2 = cnt[2] % 2;

    if (cnt1 > 0) {
        if (cnt2 == 1) cnt1 += 2;
        ans += (cnt1 - 1) / 4 + 1;
    } else if (cnt3 > 0) {
        ans += (cnt2 + cnt3);
    } else {
        ans += cnt2;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}