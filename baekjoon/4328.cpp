#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int b;
    while (cin >> b && b > 0) {
        string p, m;
        cin >> p >> m;

        int pn = p.size();
        int mn = m.size();

        long long mtmp = 0;
        long long tmp = 1;
        for (int i = 0; i < mn; i++) {
            mtmp += tmp * (m[mn - i -1] - '0');
            tmp *= b;
        }

        vector<long long> r(pn);
        tmp = 1;
        for (int i = 0; i < pn; i++) {
            r[pn - i - 1] = tmp % mtmp;
            tmp *= b;
            tmp %= mtmp;
        }

        long long ansi = 0;
        for (int i = 0; i < pn; i++) {
            ansi += (((long long) (p[i] - '0') * r[i]) % mtmp);
            ansi %= mtmp;
        }

        string ans = "";
        while (ansi > 0) {
            ans = (char) ((ansi % b) + '0') + ans;
            ansi /= b;
        }

        if (ans == "") cout << 0 << '\n';
        else cout << ans << '\n';
    }
}