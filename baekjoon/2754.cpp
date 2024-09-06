#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string g;
    cin >> g;

    if (g == "A+") cout << 4.3 << '\n';
    else if (g == "A0") cout << "4.0\n";
    else if (g == "A-") cout << "3.7\n";
    else if (g == "B+") cout << "3.3\n";
    else if (g == "B0") cout << "3.0\n";
    else if (g == "B-") cout << "2.7\n";
    else if (g == "C+") cout << "2.3\n";
    else if (g == "C0") cout << "2.0\n";
    else if (g == "C-") cout << "1.7\n";
    else if (g == "D+") cout << "1.3\n";
    else if (g == "D0") cout << "1.0\n";
    else if (g == "D-") cout << "0.7\n";
    else cout << "0.0\n";
}