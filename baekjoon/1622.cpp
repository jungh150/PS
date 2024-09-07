#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s1, s2;
    while (getline(cin, s1)) {
        getline(cin, s2);
        int cnt1[26] = {};
        int cnt2[26] = {};
        for (char c: s1) cnt1[c - 'a']++;
        for (char c: s2) cnt2[c - 'a']++;
        for (int i = 0; i < 26; i++) {
            int n = min(cnt1[i], cnt2[i]);
            while (n--) cout << char('a' + i);
        }
        cout << '\n';
    }
}