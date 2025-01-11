#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n - 1; i++) cin >> a[i];
    a[n - 1] = k + 1;

    vector<int> cnt;
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp++;
        if (a[i] > k) {
            cnt.push_back(tmp);
            tmp = 0;
        }
    }
    cnt.push_back(0);

    int ans = 0;
    for (int i = 1; i < cnt.size(); i++) {
        ans = max(ans, cnt[i] + cnt[i - 1]);
    }

    cout << ans << '\n';
}