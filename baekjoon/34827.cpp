#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int x = 0;
    int y = 0;
    vector<bool> used(26, 0);
    used[s[0] - 'A'] = 1;
    for (int i = 1; i < n; i++) {
        used[s[i] - 'A'] = 1;
        if (s[i - 1] < s[i]) x++;
        else y++;
    }

    if (abs(x - y) <= 1) {
        cout << n << '\n' << s << '\n';
        return;
    }

    string ans = "";
    ans += s;

    if (x > y) {
        int need = x - y - 1; // y가 더 필요
        int idx = s[n - 1] - 'A' - 1;
        
        while (need > 0) {
            if (idx < 0) {
                for (int i = 25; i >= 0; i--) {
                    if (!used[i]) {
                        used[i] = true;
                        ans += ((char) (i + 'A'));
                        idx = i;
                        need++;
                        break;
                    }
                }
            }

            if (!used[idx]) {
                used[idx] = true;
                ans += ((char) (idx + 'A'));
                idx--;
                need--;
            } else {
                idx--;
            }
        }
    } else {
        int need = y - x - 1; // x가 더 필요
        int idx = s[n - 1] - 'A' + 1;

        while (need > 0) {
            if (idx >= 26) {
                for (int i = 0; i < 26; i++) {
                    if (!used[i]) {
                        used[i] = true;
                        ans += ((char) (i + 'A'));
                        idx = i;
                        need++;
                        break;
                    }
                }
            }

            if (!used[idx]) {
                used[idx] = true;
                ans += ((char) (idx + 'A'));
                idx++;
                need--;
            } else {
                idx++;
            }
        }
    }

    cout << ans.size() << '\n' << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}