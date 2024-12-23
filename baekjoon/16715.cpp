#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int maxa = 0;
    int base = 0;

    for (int i = 2; i <= n; i++) {
        int tmp = n;
        int suma = 0;
        while (tmp > 0) {
            suma += (tmp % i);
            tmp /= i;
        }
        if (suma > maxa) {
            maxa = suma;
            base = i;
        }
    }

    cout << maxa << ' ' << base << '\n';
}