#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double n;
    cin >> n;

    cout << fixed;
    cout.precision(2);

    cout << n / 4 << '\n';
}