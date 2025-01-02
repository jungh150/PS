#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;

    int state = 0;
    int lever = 5;

    for (char c: s) {
        if (state >= 2) break;

        if (c == 'P') {
            if (state == 1) {
                lever = 6;
            } else {
                if (lever == 5) lever = 1;
                else if (lever == 1) lever = 5;
            }
        } else if (c == 'W') {
            state++;
        }
    }

    if (state < 2) cout << 0 << '\n';
    else cout << lever << '\n';
}