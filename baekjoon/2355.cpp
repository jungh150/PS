#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long a, b;
    cin >> a >> b;

    if (a > b) swap(a, b); // now a <= b

    long long suma = (a + b) * (b - a + 1) / 2;

    cout << suma << '\n';
}