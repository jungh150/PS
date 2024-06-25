#include <iostream>
#include <vector>
using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, n;
    cin >> t;

    while (t--) {
        cin >> n;
        vector<int> num(n);
        vector<int> dif(n - 1);
        bool inf = true;

        for (int i = 0; i < n; i++) {
            cin >> num[i];
            if (i == 0) continue;
            dif[i - 1] = abs(num[i] - num[i - 1]);
            if (num[i] != num[i - 1]) inf = false;
        }

        int ans = gcd(dif[0], dif[1]);
        for (int i = 2; i < n - 1; i++) {
            ans = gcd(ans, dif[i]);
        }

        if (inf) cout << "INFINITY\n";
        else cout << ans << '\n';
    }
}