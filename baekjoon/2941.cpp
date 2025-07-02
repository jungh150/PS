#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans++;
        if (s[i] == 'c' && i + 1 < n) {
            if (s[i + 1] == '=' || s[i + 1] == '-') i++;
        } else if (s[i] == 'd') {
            if (i + 2 < n && s[i + 1] == 'z' && s[i + 2] == '=') i += 2;
            else if (i + 1 < n && s[i + 1] == '-') i++;
        } else if (s[i] == 'l' && i + 1 < n) {
            if (s[i + 1] == 'j') i++;
        } else if (s[i] == 'n' && i + 1 < n) {
            if (s[i + 1] == 'j') i++;
        } else if (s[i] == 's' && i + 1 < n) {
            if (s[i + 1] == '=') i++;
        } else if (s[i] == 'z' && i + 1 < n) {
            if (s[i + 1] == '=') i++;
        }
    }

    cout << ans << '\n';
}