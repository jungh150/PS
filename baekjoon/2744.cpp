#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    for (char c: str) {
        if (c >= 'a' && c <= 'z') {
            cout << (char) (c + 'A' - 'a');
        } else {
            cout << (char) (c - 'A' + 'a');
        }
    }
    cout << '\n';
}