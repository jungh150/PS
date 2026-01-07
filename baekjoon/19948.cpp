#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string s;
    getline(cin, s);
    int n = s.size();

    int k;
    cin >> k;

    vector<int> a(26);
    for (int i = 0; i < 26; i++) cin >> a[i];

    string ans = "";
    if (s[0] <= 'Z') ans += s[0];
    else ans += (s[0] - 'a' + 'A');
    for (int i = 1; i < n; i++) {
        if (s[i - 1] != s[i]) {
            if (s[i - 1] == ' ') k--;
            else if (s[i - 1] <= 'Z') a[s[i - 1] - 'A']--;
            else a[s[i - 1] - 'a']--;
        }

        if (s[i - 1] == ' ' && s[i] != ' ') {
            if (s[i] <= 'Z') ans += s[i];
            else ans += (s[i] - 'a' + 'A');
        }
    }
    if (s[n - 1] == ' ') k--;
    else if (s[n - 1] <= 'Z') a[s[n - 1] - 'A']--;
    else a[s[n - 1] - 'a']--;

    s = ans;
    n = s.size();
    for (int i = 1; i < n; i++) {
        if (s[i - 1] != s[i]) {
            if (s[i - 1] == ' ') k--;
            else if (s[i - 1] <= 'Z') a[s[i - 1] - 'A']--;
            else a[s[i - 1] - 'a']--;
        }
    }
    if (s[n - 1] == ' ') k--;
    else if (s[n - 1] <= 'Z') a[s[n - 1] - 'A']--;
    else a[s[n - 1] - 'a']--;

    if (k < 0) {
        cout << "-1\n";
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (a[i] < 0) {
            cout << "-1\n";
            return;
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