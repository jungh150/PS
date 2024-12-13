#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    getline(cin, s);
    
    for (char c: s) {
        if (c >= 'a' && c <= 'z') {
            if (c + 13 > 'z') cout << char(c - 13);
            else cout << char(c + 13);
        } else if (c >= 'A' && c <= 'Z') {
            if (c + 13 > 'Z') cout << char(c - 13);
            else cout << char(c + 13);
        } else {
            cout << c;
        }
    }
    cout << '\n';
}