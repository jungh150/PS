#include <iostream>
#include <vector>
using namespace std;

int fact(int x) {
    if (x == 0 || x == 1) return 1;
    else return x * fact(x - 1);
}

int comb(int a, int b) {
    return fact(a) / (fact(b) * fact(a - b));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    double e1 = (double) (10000 * 6 + 1000 * 21) / (6 * 6 * 6);

    double e2 = (double) (1000 * 6 + 100 * 21) * 5 * 3 / (6 * 6 * 6);

    double e3 = 0;
    for (int i = 3; i < 7; i++) {
        e3 += (double) (i * 100) * comb(i - 1, 2) * 6 / (6 * 6 * 6);
    }

    cout << fixed;
    cout.precision(10);
    cout << e1 << '\n';
    cout << e2 << '\n';
    cout << e3 << '\n';
    cout << e1 + e2 + e3 << '\n';

    cout << (double) 16000 / 216 << '\n';
    cout << e1 + e2 + e3 - (double) 16000 / 216 << '\n';
}