#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = a[i];
        int skip = -1;
        int cnt = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] == cur) cnt++;
            else if (skip == -1) skip = a[j];
            else if (a[j] != skip) break;
        }
        ans = max(ans, cnt);
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