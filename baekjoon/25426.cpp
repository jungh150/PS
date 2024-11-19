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

    vector<long long> a(n);
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int b;
        cin >> a[i] >> b;
        ans += b;
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++) {
        ans += (i + 1) * a[i];
    }

    cout << ans << '\n';
}