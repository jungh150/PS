#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c;
    cin >> a >> b >> c;
    int s = a + b + c;

    if (s == 180) {
        if (a == b && b == c) cout << "Equilateral\n";
        else if (a == b || b == c || c == a) cout << "Isosceles\n";
        else cout << "Scalene\n";
    } else {
        cout << "Error\n";
    }
}