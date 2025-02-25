#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, e;
    cin >> n >> e;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] - a[i - 1] >= e) ans++;
    }

    cout << ans << '\n';
}