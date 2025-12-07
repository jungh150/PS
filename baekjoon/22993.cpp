#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n - 1);
    long long cur;
    cin >> cur;
    for (int i = 0; i < n - 1; i++) cin >> a[i];

    sort(a.begin(), a.end());
    for (int i = 0; i < n - 1; i++) {
        if (cur > a[i]) {
            cur += a[i];
        } else {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}