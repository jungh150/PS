#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n % 8 == 1) cout << 1 << '\n';
    else if (n % 8 == 2) cout << 2 << '\n';
    else if (n % 8 == 3) cout << 3 << '\n';
    else if (n % 8 == 4) cout << 4 << '\n';
    else if (n % 8 == 5) cout << 5 << '\n';
    else if (n % 8 == 6) cout << 4 << '\n';
    else if (n % 8 == 7) cout << 3 << '\n';
    else if (n % 8 == 0) cout << 2 << '\n';
}