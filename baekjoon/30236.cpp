#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int pre = 0;
    for (int i = 0; i < n; i++) {
        int cur;
        if (pre + 1 == a[i]) cur = pre + 2;
        else cur = pre + 1;
        pre = cur;
    }

    cout << pre << '\n';
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