#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, t;
    cin >> n >> t;

    vector<int> a(t);
    vector<int> b(n - t);
    for (int i = 0; i < t; i++) cin >> a[i];
    for (int i = 0; i < n - t; i++) cin >> b[i];

    sort(a.begin(), a.end());
    for (int i = 0; i < t; i++) cout << a[i] << ' ';
    for (int i = 0; i < n - t; i++) cout << b[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}