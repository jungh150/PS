#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int cur = n;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == cur) cur--;
    }

    cout << cur << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}