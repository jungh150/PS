#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    if (s == "NLCS") cout << "North London Collegiate School\n";
    else if (s == "BHA") cout << "Branksome Hall Asia\n";
    else if (s == "KIS") cout << "Korea International School\n";
    else if (s == "SJA") cout << "St. Johnsbury Academy\n";
}