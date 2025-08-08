#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if ((n / 10) == (n % 10)) cout << 1 << '\n';
    else cout << 0 << '\n';
}