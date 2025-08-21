#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve() {
    int n, m;
    string a, b, c;

    cin >> n >> a >> m >> b >> c;

    for (int i = 0; i < m; i++) {
        if (c[i] == 'V') a = b[i] + a;
        else if (c[i] == 'D') a += b[i];
    }

    cout << a << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}