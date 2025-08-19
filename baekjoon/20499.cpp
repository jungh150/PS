#include <iostream>
using namespace std;

void solve() {
    int k, d, a;
    char c;
    cin >> k >> c >> d >> c >> a;
    if (k + a < d || d == 0) cout << "hasu\n";
    else cout << "gosu\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}