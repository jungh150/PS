#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    if (str == "fdsajkl;" || str == "jkl;fdsa") cout << "in-out\n";
    else if (str == "asdf;lkj" || str == ";lkjasdf") cout << "out-in\n";
    else if (str == "asdfjkl;") cout << "stairs\n";
    else if (str == ";lkjfdsa") cout << "reverse\n";
    else cout << "molu\n";
}