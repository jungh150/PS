#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, t;
    cin >> n >> t;

    vector<int> d;
    for (int i = 1; i <= t; i++) {
        if (t % i == 0) d.push_back(i);
    }

    int ans = 0;
    while (n--) {
        int a;
        cin >> a;
        int idx = lower_bound(d.begin(), d.end(), a) - d.begin();
        if (idx == 0) ans += abs(a - d[idx]);
        else ans += min(abs(a - d[idx]), abs(a - d[idx - 1]));
    }
    cout << ans << '\n';
}