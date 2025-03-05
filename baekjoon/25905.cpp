#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double ans = 1000000000;

    double a[10];
    for (int i = 0; i < 10; i++) cin >> a[i];

    sort(a, a + 10);

    for (int i = 1; i < 10; i++) ans *= (a[i] / i);

    cout.precision(8);
    cout << ans << '\n';
}