#include <iostream>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    int minv = 1e8;
    int mini = -1;

    for (int i = 1; i < k + 1; i++) {
        int f, d;
        cin >> f >> d;
        int tmp = (f - 1) + (m - d);
        if (tmp < minv) {
            minv = tmp;
            mini = i;
        }
    }

    cout << mini << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}