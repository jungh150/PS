#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    string ans = "";
    int cnt = 0;

    while (cin >> s) {
        cnt++;
        if ((cnt != 1) && (s == "i" || s == "pa" || s == "te" || s == "ni" || s == "niti" || s == "a" || s == "ali" || s == "nego" || s == "no" || s == "ili")) {
            continue;
        }
        ans += s[0] + ('A' - 'a');
    }

    cout << ans << '\n';
}