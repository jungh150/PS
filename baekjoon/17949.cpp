#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    int n;
    cin >> n;

    int idx = 0;
    while (n--) {
        string t;
        cin >> t;

        int m;
        if (t == "char") m = 2;
        else if (t == "int") m = 8;
        else if (t == "long_long") m = 16;

        long long ans = 0;
        long long tmp = 1;
        for (int i = m - 1; i >= 0; i--) {
            char c = s[idx + i];
            int co;
            if (c >= '0' && c <= '9') co = c - '0';
            else if (c >= 'a' && c <= 'f') co = c - 'a' + 10;
            ans += co * tmp;
            tmp *= 16;
        }

        cout << ans << ' ';

        idx += m;
    }
    cout << '\n';
}