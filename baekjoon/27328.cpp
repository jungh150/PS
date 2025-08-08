#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b;
    cin >> a >> b;

    if (a < b) cout << -1 << '\n';
    else if (a == b) cout << 0 << '\n';
    else cout << 1 << '\n';
}