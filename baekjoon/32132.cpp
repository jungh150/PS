#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    string ans = "";
    for (int i = 0; i < n; i++) {
        if (s[i] == '4' || s[i] == '5') {
            if (!(ans.size()  - 2 >= 0 && ans[ans.size() - 1] == 'S' && ans[ans.size()  - 2] == 'P')) ans += s[i];
        } else {
            ans += s[i];
        }
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