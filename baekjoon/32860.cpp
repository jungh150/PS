#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    cout << "SN " << n;

    if (m <= 26) {
        cout << char('A' + m - 1) << '\n';
    } else {
        string s = "";
        m -= 27;
        char first = 'a' + m / 26;
        char second = 'a' + m % 26;
        cout << first << second << '\n';
    }
}