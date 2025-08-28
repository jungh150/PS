#include <iostream>
using namespace std;

void solve() {
    int c;
    cin >> c;

    int ans = 0;
    while (c--) {
        string s;
        cin >> s;
        int idx = 0;
        int cnt = 0;
        while (idx < s.size()) {
            if (idx + 2 < s.size() && s.substr(idx, 3) == "for") {
                cnt++;
                idx += 3;
            } else if (idx + 4 < s.size() && s.substr(idx, 5) == "while") {
                cnt++;
                idx += 5;
            } else {
                idx++;
            }
        }
        ans = max(ans, cnt);
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