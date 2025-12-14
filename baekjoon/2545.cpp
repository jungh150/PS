#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    vector<long long> a(3);
    long long d;

    cin >> a[0] >> a[1] >> a[2] >> d;
    sort(a.begin(), a.end());

    long long x = a[0] + a[1] + a[2] - d;
    a[0] = min(x / 3, a[0]);
    x -= a[0];
    a[1] = min(x / 2, a[1]);
    x -= a[1];

    cout << a[0] * a[1] * x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}