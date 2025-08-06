#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double w, h;
    cin >> w >> h;

    double ans = w * h / 2;

    cout << fixed;
    cout.precision(1);
    cout << ans << '\n';
}