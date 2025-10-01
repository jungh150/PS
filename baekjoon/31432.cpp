#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];

    cout << "YES\n";
    int tmp = d[n - 1];
    if (tmp == 0 || tmp == 1) cout << tmp << '\n';
    else cout << tmp << tmp << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}