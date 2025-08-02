#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, s;
    cin >> t >> s;

    if ((t <= 11 || t > 16) || (s == 1)) cout << 280 << '\n';
    else cout << 320 << '\n';
}