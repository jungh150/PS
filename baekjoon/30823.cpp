#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string ans;
    ans.resize(n);

    if ((n + k) % 2 == 1) {
        for (int i = 0; i < k - 1; i++) {
            ans[n - k + 1 + i] = s[i];
        }
    } else {
        for (int i = 0; i < k - 1; i++) {
            ans[n - i - 1] = s[i];
        }
    }

    for (int i = k - 1; i < n; i++) {
        ans[i - k + 1] = s[i];
    }

    cout << ans << '\n';
}