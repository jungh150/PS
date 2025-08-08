#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    int q = n / 5;
    int r = n % 5;

    while (q--) cout << "V";
    while (r--) cout << "I";
    cout << '\n';
}