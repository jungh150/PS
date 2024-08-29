#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int l;
    double r;
    cin >> l >> r;
    int c = 1;
    int sum = 0;

    while (true) {
        c *= 2;
        l = int(l * r / 100);
        if (l <= 5) break;
        sum += c * l;
    }

    cout << sum << '\n';
}