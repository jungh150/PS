#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r1, r2, s;
    cin >> r1 >> s;

    r2 = s * 2 - r1;
    cout << r2 << '\n';
}