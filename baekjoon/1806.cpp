#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int si = 0;
    int ei = 1;
    int sumt = a[0];
    int ans = 200000;
    int cnt = 1;
    while (ei <= n) {
        if (sumt < s) {
            sumt += a[ei];
            ei++;
            cnt++;
        } else {
            ans = min(ans, cnt);
            sumt -= a[si];
            si++;
            cnt--;
        }
    }

    if (ans == 200000) cout << 0 << '\n';
    else cout << ans << '\n';
}