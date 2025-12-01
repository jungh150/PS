#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    if (k == 0) {
        if (n == 1 && m == 1) {
            cout << "0\n";
            return;
        } else if (n == 1 && m == 2) {
            cout << "0 0\n";
            return;
        } else if (n == 2 && m == 1) {
            cout << "0\n0\n";
            return;
        } else {
            cout << "-1\n";
            return;
        }
    }

    bool rev = false;
    if (n == 1 || m == 1) {
        if (m == 1) {
            swap(n, m); // now, n == 1
            rev = true;
        }
    } else {
        cout << "-1\n";
        return;
    }

    vector<vector<ll>> ans(n, vector<ll>(m));

    ll val = 0;
    for (int j = 0; j < m; j += 2) {
        ans[0][j] = val;
        val += (k + 1);
    }
    val = 1;
    for (int j = 1; j < m; j += 2) {
        ans[0][j] = val;
        val += (k + 1);
    }

    if (rev) {
        for (int j = 0; j < m; j++) cout << ans[0][j] << '\n';
    } else {
        for (int j = 0; j < m; j++) cout << ans[0][j] << ' ';
        cout << '\n';
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