#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<bool> chk(n + 1, false);
    int cnt = 0;
    int ans = 0;

    for (int i = 0; i < 2 * n; i++) {
        int x;
        cin >> x;
        
        if (chk[x]) {
            chk[x] = false;
            cnt--;
        } else {
            chk[x] = true;
            cnt++;
            ans = max(ans, cnt);
        }
    }

    cout << ans << '\n';
}