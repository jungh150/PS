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

        vector<int> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        int pre = arr[0];
        string ans = "YES";

        for (int i = 1; i < n; i++) {
            int cur = arr[i];
            if (cur <= pre) {
                pre = cur;
                continue;
            }

            // pre = a + b, cur = a + c

            bool flag = false;
            int minc = (pre + 2) / 2;
            int maxc = pre;
            for (int c = minc + 1; c <= maxc; c++) {
                int a = cur - c;
                int b = pre - a;
                if (a < b && b < c && c <= a + b) {
                    flag = true;
                    break;
                }
            }

            if (!flag) {
                ans = "NO";
                break;
            }
            
            pre = cur;
        }

        cout << ans << '\n';
    }
}