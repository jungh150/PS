#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = 1000000000;
    for (int k = 0; k < n; k++) {
        vector<int> at = a;
        int cnt = 0;
        for (int i = n - 1; i > 0; i--) {
            if (i == k) {
                reverse(at.begin(), at.end());
                cnt++;
            }
            for (int j = 0; j < i; j++) {
                if (at[j] > at[j + 1]) {
                    int tmp = at[j];
                    at[j] = at[j + 1];
                    at[j + 1] = tmp;
                    cnt++;
                }
            }
        }
        ans = min(ans, cnt);
    }

    cout << ans << '\n';
}