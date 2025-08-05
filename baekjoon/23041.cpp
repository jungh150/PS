#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n, m;
    cin >> n >> m;

    long long g = gcd(n, m);

    if ((n / g + m / g) % 2 == 1) cout << g * g << '\n';
    else cout << 2 * g * g << '\n';
}