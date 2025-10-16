#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> s(n + 1, 0);
    vector<long long> ps(n + 1, 0);
    long long ans = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> s[i];
        ps[i] = ps[i - 1] - s[i];
        ans = max(ans, ps[i - 1] + s[i]);
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