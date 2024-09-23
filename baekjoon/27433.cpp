#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    long long f = 1;
    for (int i = 2; i < n + 1; i++) f *= i;

    cout << f << '\n';
}