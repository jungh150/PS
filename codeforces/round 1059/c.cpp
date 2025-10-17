#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b;
    cin >> a >> b;

    if (a == b) {
        cout << 0 << '\n';
        return;
    }

    vector<int> bina;
    vector<int> binb;

    for (int i = 0; i < 40; i++) {
        if (a % 2 == 1) bina.push_back(1);
        else bina.push_back(0);
        a /= 2;
        if (a == 0) break;
    }

    for (int i = 0; i < 40; i++) {
        if (b % 2 == 1) binb.push_back(1);
        else binb.push_back(0);
        b /= 2;
        if (b == 0) break;
    }

    // for (int x: bina) cout << x << ' ';
    // cout << '\n';

    // for (int x: binb) cout << x << ' ';
    // cout << '\n';

    if (bina.size() < binb.size()) {
        cout << -1 << '\n';
        return;
    }

    cout << 2 << '\n';

    long long x1 = 0;
    for (int i = 0; i < bina.size(); i++) {
        if (bina[i] == 0) x1 += (1LL << i);
    }
    cout << x1 << ' ';

    long long x2 = 0;
    for (int i = 0; i < bina.size(); i++) {
        if (i >= binb.size() || binb[i] == 0) x2 += (1LL << i);
    }
    cout << x2 << '\n';
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