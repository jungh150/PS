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
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        string ans = "L";
        int pre = a[0];
        int l = 1;
        int r = n - 1;
        while (l < r) {
            if (a[l] > pre && a[r] > pre) {
                if (a[l] > a[r]) {
                    ans += "LR";
                    pre = a[r];
                } else {
                    ans += "RL";
                    pre = a[l];
                }
            } else if (a[l] < pre && a[r] < pre) {
                if (a[l] < a[r]) {
                    ans += "LR";
                    pre = a[r];
                }
                else {
                    ans += "RL";
                    pre = a[l];
                }
            } else {
                // no matter
                ans += "RL";
                pre = a[l];
            }
            l++;
            r--;
        }
        if (l == r) ans += 'L';

        cout << ans << '\n';
    }
}