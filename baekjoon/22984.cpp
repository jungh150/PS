#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    double ans = 0;

    vector<double> p = vector<double>(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        ans += p[i];
    }

    for (int i = 0; i < n - 1; i++) {
        ans += p[i] * (1 - p[i + 1]) + (1 - p[i]) * p[i + 1];
    }

    cout << fixed;
    cout.precision(6);
    cout << ans << '\n';
}