#include <iostream>
using namespace std;

void solve() {
    int t1, e1, f1, t2, e2, f2;
    cin >> t1 >> e1 >> f1 >> t2 >> e2 >> f2;

    int sum1 = 3 * t1 + 20 * e1 + 120 * f1;
    int sum2 = 3 * t2 + 20 * e2 + 120 * f2;

    if (sum1 > sum2) cout << "Max\n";
    else if (sum1 == sum2) cout << "Draw\n";
    else cout << "Mel\n";
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