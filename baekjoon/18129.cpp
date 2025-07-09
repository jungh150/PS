#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<bool> used(26, false);

    string s;
    int k;
    cin >> s >> k;

    int n = s.size();
    int cnt = 1;
    string ans = "";
    for (int i = 1; i < n; i++) {
        if (tolower(s[i]) == tolower(s[i - 1])) {
            cnt++;
        } else {
            char c = tolower(s[i - 1]);
            if (!used[c - 'a']) {
                if (cnt >= k) ans += '1';
                else ans += '0';
                used[c - 'a'] = true;
            }
            cnt = 1;
        }
    }
    char c = tolower(s[n - 1]);
    if (!used[c - 'a']) {
        if (cnt >= k) ans += '1';
        else ans += '0';
    }

    cout << ans << '\n';
}