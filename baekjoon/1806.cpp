#include <iostream>
#include <vector>
using namespace std;

int MAX_INT = 100000;

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
    int ans = MAX_INT;
    int cnt = 1;
    while (ei <= n) {
        if (sumt < s) { // sumt가 s보다 작으면 뒤쪽 원소 하나 추가
            sumt += a[ei];
            ei++;
            cnt++;
        } else { // 크면 갱신 후 앞쪽 원소 하나 제거
            ans = min(ans, cnt);
            sumt -= a[si];
            si++;
            cnt--;
        }
    }

    if (ans == MAX_INT) cout << 0 << '\n';
    else cout << ans << '\n';
}