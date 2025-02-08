#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long s = 1, e = 1e12 + 1;
    long long ans = e;

    while (s <= e) {
        long long mid = (s + e) / 2;
        long long tmp = 0;

        for (int x: a) {
            tmp += mid / x;
            if (tmp >= m) break;
        }

        if (tmp < m) {
            s = mid + 1;
        } else {
            ans = mid;
            e = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}