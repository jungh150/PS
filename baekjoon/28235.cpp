#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    if (s == "SONGDO") cout << "HIGHSCHOOL\n";
    else if (s == "CODE") cout << "MASTER\n";
    else if (s == "2023") cout << "0611\n";
    else if (s == "ALGORITHM") cout << "CONTEST\n";
}