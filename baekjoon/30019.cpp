#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int k, s, e;
        cin >> k >> s >> e;
        if (a[k] <= s) {
            cout << "YES\n";
            a[k] = e;
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}