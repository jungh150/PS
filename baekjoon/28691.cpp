#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char c;
    cin >> c;

    if (c == 'M') cout << "MatKor\n";
    else if (c == 'W') cout << "WiCys\n";
    else if (c == 'C') cout << "CyKor\n";
    else if (c == 'A') cout << "AlKor\n";
    else if (c == '$') cout << "$clear\n";
}