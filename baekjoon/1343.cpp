#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    string ans = "";

    int cnt = 0;
    for (char c: s) {
        if (c == '.') {
            if (cnt % 2 != 0) {
                cout << -1 << '\n';
                return 0;
            }
            int tmp = cnt / 4;
            if (cnt % 4 == 0) {
                for (int i = 0; i < tmp; i++) ans += "AAAA";
            } else {
                for (int i = 0; i < tmp; i++) ans+= "AAAA";
                ans += "BB";
            }
            ans += '.';
            cnt = 0;
        } else if (c == 'X') {
            cnt++;
        }
    }
    
    if (cnt % 2 != 0) {
        cout << -1 << '\n';
        return 0;
    }
    int tmp = cnt / 4;
    if (cnt % 4 == 0) {
        for (int i = 0; i < tmp; i++) ans += "AAAA";
    } else {
        for (int i = 0; i < tmp; i++) ans += "AAAA";
        ans += "BB";
    }

    cout << ans << '\n';
}