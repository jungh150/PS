#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    int coe = 0;
    int sumt = 0;

    for (int i = 0; i < 13; i++) {
        if (i % 2 == 0) {
            if (s[i] == '*') coe = 1;
            else sumt += 1 * (s[i] - '0');
        } else {
            if (s[i] == '*') coe = 3;
            else sumt += 3 * (s[i] - '0');
        }
    }

    sumt = sumt % 10;
    for (int i = 0; i < 10; i++) {
        if ((sumt + coe * i) % 10 == 0) {
            cout << i << '\n';
            break;
        }
    }
}