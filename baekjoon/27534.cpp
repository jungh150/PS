#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        
        if (n == 1 || n == 3) {
            cout << -1 << '\n';
        } else if (n == 2) {
            if (s[0] == s[1]) cout << 1 << '\n';
            else cout << 0 << '\n';
        } else {
            if (s[0] == s[n - 1]) { // 양끝 동일
                if (s[1] == s[n - 2]) cout << 2 << '\n';
                else cout << 1 << '\n';
            } else { // 양끝 다름
                if (s[0] == s[n - 2] && s[1] == s[n - 1]) cout << 0 << '\n';
                else if (s[1] == s[n - 2]) cout << 1 << '\n';
                else {
                    int l = 0;
                    while (s[l] == s[0]) l++;
                    int r = n - 1;
                    while (s[r] == s[n - 1]) r--;

                    if (l - 0 == (n - 1) - r) cout << 0 << '\n';
                    else if ((n % 2 == 1) && (r + 1 == l) && (l == n / 2 || r == n / 2)) cout << 2 << '\n';
                    else cout << 1 << '\n';
                }
            }
        }
    }
}