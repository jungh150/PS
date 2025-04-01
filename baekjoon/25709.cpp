#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int ans = 0;

    string s = to_string(n);
    string tmps = "";

    for (char c: s) {
        if (c == '1') ans++;
        else tmps += c;
    }

    if (tmps.empty()) n = 0;
    else n = stoi(tmps);

    while (n > 0) {
        int tmp = n % 10;

        if (tmp == 0) {
            n -= 9;
            ans += 9;
        } else if (tmp == 1) {
            ans++;
            n /= 10;
        } else {
            n -= (tmp - 1);
            ans += (tmp - 1);
        }
    }

    cout << ans << '\n';
}