#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int l, a, b, c, d;
    cin >> l >> a >> b >> c >> d;

    int cant = max((a - 1) / c + 1, (b - 1) / d + 1);
    cout << l - cant << '\n';
}