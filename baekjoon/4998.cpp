#include <iostream>
using namespace std;

void solve() {
    double n, b, m;
    while (cin >> n) {
        cin >> b >> m;
        int cnt = 0;
        while (1) {
            n += (n * b / 100);
            cnt++;
            if (n > m) {
                cout << cnt << '\n';
                break;
            }
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