#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    while (n--) {
        string s;
        cin >> s;

        for (char c: s) {
            if (c >= 'A' && c <= 'Z') cout << char(c - ('A' - 'a'));
            else cout << c;
        }
        cout << '\n';
    }
}