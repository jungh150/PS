#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    int ans = 0;
    for (char c: s) {
        if (c == 'A' || c == 'B' || c == 'C') ans += 3;
        else if (c == 'D' || c == 'E' || c == 'F') ans += 4;
        else if (c == 'G' || c == 'H' || c == 'I') ans += 5;
        else if (c == 'J' || c == 'K' || c == 'L') ans += 6;
        else if (c == 'M' || c == 'N' || c == 'O') ans += 7;
        else if (c == 'P' || c == 'Q' || c == 'R' || c == 'S') ans += 8;
        else if (c == 'T' || c == 'U' || c == 'V') ans += 9;
        else if (c == 'W' || c == 'X' || c == 'Y' || c == 'Z') ans += 10;
    }

    cout << ans << '\n';
}