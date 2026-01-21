#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> ps(n + 1, 0);
    int ans = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) ps[i] = max(ps[i], ps[j] + 1);
        }
        ans = max(ans, ps[i]);
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