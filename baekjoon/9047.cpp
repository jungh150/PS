#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    while (1) {
        if (n == 6174) break;

        vector<int> a(4);
        for (int i = 0; i < 4; i++) {
            a[i] = n % 10;
            n = n / 10;
        }

        sort(a.begin(), a.end());
        n = (a[3] * 1000 + a[2] * 100 + a[1] * 10 + a[0]) - (a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3]);
        ans++;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}