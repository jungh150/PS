#include <iostream>
using namespace std;

int MAX_SIZE = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    if (n <= 1) {
        cout << 1 << '\n';
    } else if (n <= 3) {
        cout << 2 << '\n';
    } else if (n <= 6) {
        cout << 3 << '\n';
    } else if (n <= 10) {
        cout << 4 << '\n';
    } else if (n <= 15) {
        cout << 5 << '\n';
    } else if (n <= 21) {
        cout << 6 << '\n';
    } else {
        long long tmp = (n + 6) / 7; // ceil(n / 7)
        cout << tmp + 3 << '\n';
    }
}