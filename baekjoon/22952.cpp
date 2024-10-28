#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n % 2 == 1) {
        for (int i = 1; i < n / 2 + 1; i++) {
            cout << i << ' ' << n - i << ' ';
        }
        cout << n << '\n';
    } else {
        for (int i = 1; i < n / 2; i++) {
            cout << i << ' ' << n - i << ' ';
        }
        cout << n / 2 << ' ' << n << '\n';
    }
}