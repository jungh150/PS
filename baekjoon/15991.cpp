#include <iostream>
using namespace std;

int mod = 1000000009;
long long s[100001] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    s[1] = 1;
    s[2] = 2;
    s[3] = 4;
    for (int i = 4; i < 100001; i++) {
        s[i] = (s[i - 1] + s[i - 2] + s[i - 3]) % mod;
    }

    int t;
    cin >> t;

    for (int tn = 0; tn < t; tn++) {
        int n;
        cin >> n;

        long long ans = 0;
        if (n == 1 || n == 2) {
            ans = n;
        } else if (n == 3) {
            ans = 2;
        } else if (n % 2 == 0) {
            ans = (s[n / 2] + s[(n - 2) / 2]) % mod;
        } else {
            ans = (s[(n - 1) / 2] + s[(n - 3) / 2]) % mod;
        }
        cout << ans << '\n';
    }
}