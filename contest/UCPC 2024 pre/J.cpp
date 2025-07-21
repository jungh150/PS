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
        string str;
        cin >> str;
        
        int cnt = 0;
        int ans = 0;

        for(int i = 0; i < n; i++) {
            if (str[i] == 'H' || i == n - 1) {
                if (cnt % 2 == 0) {
                    ans += cnt / 2;
                } else {
                    ans = -1;
                    break;
                }
                cnt = 0;
            } else {
                cnt++;
            }
        }

        cout << ans << '\n';
    }
}