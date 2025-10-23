#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> b(n);
    vector<int> c;

    int m = (n - 1) / 2;
    int idx = 1;
    for (int i = 1; i <= n; i += 2) {
        b[m] = idx++;
        c.push_back(m + 1);
        if (m + i >= n) break;
        b[m + i] = idx++;
        c.push_back(m + i + 1);
        m--;
    }

    cout << "YES\n";
    for (int x: b) cout << x << ' ';
    cout << '\n';
    for (int x: c) cout << x << ' ';
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