#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> x(1001, 0);
    vector<int> y(1001, 0);
    vector<int> z(1001, 0);

    for (int j = 0; j < n; j++) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        for (int i = min(x1, x2); i < max(x1, x2); i++) x[i]++;
        for (int i = min(y1, y2); i < max(y1, y2); i++) y[i]++;
        for (int i = min(z1, z2); i < max(z1, z2); i++) z[i]++;
    }

    int xcnt = 0;
    int ycnt = 0;
    int zcnt = 0;
    for (int i = 1; i <= 1000; i++) {
        if (x[i] == n) xcnt++;
    }
    for (int i = 1; i <= 1000; i++) {
        if (y[i] == n) ycnt++;
    }
    for (int i = 1; i <= 1000; i++) {
        if (z[i] == n) zcnt++;
    }

    cout << xcnt * ycnt * zcnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}