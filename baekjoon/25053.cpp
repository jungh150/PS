#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> maxb(11, 0);
    for (int i = 0; i < n; i++) {
        int b, d;
        cin >> b >> d;
        maxb[d] = max(maxb[d], b);
    }

    int ans = 0;
    for (int d = 1; d <= 10; d++) {
        if (maxb[d] == 0) {
            cout << "MOREPROBLEMS\n";
            return;
        } else {
            ans += maxb[d];
        }
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