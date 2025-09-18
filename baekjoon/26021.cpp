#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int cnt = 0;
    if (s[0] == 'R') cnt++;
    for (int i = 1; i < n; i++) {
        if (s[i - 1] == s[i]) cnt++;
    }

    cout << max(0, k - cnt) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}