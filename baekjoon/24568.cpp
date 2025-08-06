#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, s;
    cin >> r >> s;

    cout << r * 8 + s * 3 - 28 << '\n';
}